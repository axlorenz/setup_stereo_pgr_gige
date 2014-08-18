#ifndef INI_PGR_GIGE_STEREO_H
#define INI_PGR_GIGE_STEREO_H

#include<iostream>
#include <sstream>
#include<math.h>
#include <stdio.h>
#include "FlyCapture2.h"
#include"ros/ros.h"

using namespace std;
using namespace FlyCapture2;


class Ini_Pgr_GigE_Stereo
{

private:


    GigECamera left_cam;
    GigECamera right_cam;

    CameraInfo camerainfo_left;
    CameraInfo camerainfo_right;

    PGRGuid pgr_guid_left;
    PGRGuid pgr_guid_right;

    MACAddress mac_address_left;
    MACAddress mac_address_right;

    IPAddress ip_address_left;
    IPAddress ip_address_right;

    IPAddress submask;
    IPAddress gateway;

    unsigned int serial_left;
    unsigned int serial_right;

    unsigned int packetsize ;
    unsigned int packetdelay;

    Error error;


public:
    Ini_Pgr_GigE_Stereo();
    Ini_Pgr_GigE_Stereo(const char * const  _mac_ad_char_left, const char * const _mac_ad_char_right, const char * const _ip_ad_char_left, const char * const _ip_ad_char_right, const char * const _submask, const char * const _gateway, const unsigned int _serial_left, const unsigned int _serial_right, const unsigned int _packetsize, const unsigned int _packetdelay);

     ~Ini_Pgr_GigE_Stereo();

    MACAddress create_MAC_from_char(const char * const mac_Address );
    IPAddress create_IP_from_char(const char * const ip_Address);

    bool initialize_pgr_gige_stereosystem();
    bool force_ip_addresses();
    bool setup_packet_transport();
    bool setup_packet_transport(const unsigned int _packetsize, const unsigned int _packetdelay);


    void PrintError( Error error );


    MACAddress getMac_address_left() const;
    void setMac_address_left(const MACAddress &value);
    MACAddress getMac_address_right() const;
    void setMac_address_right(const MACAddress &value);
    IPAddress getIp_address_left() const;
    void setIp_address_left(const IPAddress &value);
    IPAddress getIp_address_right() const;
    void setIp_address_right(const IPAddress &value);
    int getSerial_left() const;
    void setSerial_left(int value);
    int getSerial_right() const;
    void setSerial_right(int value);
    int getPacketsize() const;
    void setPacketsize(int value);
    int getPacketdelay() const;
    void setPacketdelay(int value);
    CameraInfo getCamerainfo_left() const;
    void setCamerainfo_left(const CameraInfo &value);
    CameraInfo getCamerainfo_right() const;
    void setCamerainfo_right(const CameraInfo &value);

    CameraInfo get_info_cam_left();
    CameraInfo get_info_cam_right();
    IPAddress getSubmask() const;
    void setSubmask(const IPAddress &value);
    IPAddress getGateway() const;
    void setGateway(const IPAddress &value);
    Error getError() const;
    void setError(const Error &value);
    PGRGuid *getPgr_guid_left() const;
    void setPgr_guid_left(PGRGuid *value);
    PGRGuid *getPgr_guid_right() const;
    void setPgr_guid_right(PGRGuid *value);
};

#endif // INI_PGR_GIGE_STEREO_H

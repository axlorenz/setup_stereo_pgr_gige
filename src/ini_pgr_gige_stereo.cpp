#include "ini_pgr_gige_stereo.h"




MACAddress Ini_Pgr_GigE_Stereo::getMac_address_left() const
{
    return mac_address_left;
}

void Ini_Pgr_GigE_Stereo::setMac_address_left(const MACAddress &value)
{
    mac_address_left = value;
}

MACAddress Ini_Pgr_GigE_Stereo::getMac_address_right() const
{
    return mac_address_right;
}

void Ini_Pgr_GigE_Stereo::setMac_address_right(const MACAddress &value)
{
    mac_address_right = value;
}

IPAddress Ini_Pgr_GigE_Stereo::getIp_address_left() const
{
    return ip_address_left;
}

void Ini_Pgr_GigE_Stereo::setIp_address_left(const IPAddress &value)
{
    ip_address_left = value;
}

IPAddress Ini_Pgr_GigE_Stereo::getIp_address_right() const
{
    return ip_address_right;
}

void Ini_Pgr_GigE_Stereo::setIp_address_right(const IPAddress &value)
{
    ip_address_right = value;
}

int Ini_Pgr_GigE_Stereo::getSerial_left() const
{
    return serial_left;
}

void Ini_Pgr_GigE_Stereo::setSerial_left(int value)
{
    serial_left = value;
}

int Ini_Pgr_GigE_Stereo::getSerial_right() const
{
    return serial_right;
}

void Ini_Pgr_GigE_Stereo::setSerial_right(int value)
{
    serial_right = value;
}



int Ini_Pgr_GigE_Stereo::getPacketsize() const
{
    return packetsize;
}

void Ini_Pgr_GigE_Stereo::setPacketsize(int value)
{
    packetsize = value;
}

int Ini_Pgr_GigE_Stereo::getPacketdelay() const
{
    return packetdelay;
}

void Ini_Pgr_GigE_Stereo::setPacketdelay(int value)
{
    packetdelay = value;
}

CameraInfo Ini_Pgr_GigE_Stereo::getCamerainfo_left() const
{
    return camerainfo_left;
}

void Ini_Pgr_GigE_Stereo::setCamerainfo_left(const CameraInfo &value)
{
    camerainfo_left = value;
}

CameraInfo Ini_Pgr_GigE_Stereo::getCamerainfo_right() const
{
    return camerainfo_right;
}

void Ini_Pgr_GigE_Stereo::setCamerainfo_right(const CameraInfo &value)
{
    camerainfo_right = value;
}

CameraInfo Ini_Pgr_GigE_Stereo::get_info_cam_left()
{
    return this->camerainfo_left;
}

CameraInfo Ini_Pgr_GigE_Stereo::get_info_cam_right()
{
    return this->camerainfo_right;
}

IPAddress Ini_Pgr_GigE_Stereo::getSubmask() const
{
    return submask;
}

void Ini_Pgr_GigE_Stereo::setSubmask(const IPAddress &value)
{
    submask = value;
}

IPAddress Ini_Pgr_GigE_Stereo::getGateway() const
{
    return gateway;
}

void Ini_Pgr_GigE_Stereo::setGateway(const IPAddress &value)
{
    gateway = value;
}

Error Ini_Pgr_GigE_Stereo::getError() const
{
    return error;
}

void Ini_Pgr_GigE_Stereo::setError(const Error &value)
{
    error = value;
}


Ini_Pgr_GigE_Stereo::Ini_Pgr_GigE_Stereo()
{
    this->packetsize = 9000;
    this->packetdelay= 400;

    this->submask = this->create_IP_from_char("255.255.0.0");
    this->gateway = this->create_IP_from_char("0.0.0.0");
}

Ini_Pgr_GigE_Stereo::Ini_Pgr_GigE_Stereo(const char * const _mac_ad_char_left, const char * const _mac_ad_char_right, const char * const _ip_ad_char_left, const char * const _ip_ad_char_right, const char * const _submask, const char * const _gateway, const unsigned int _serial_left, const unsigned int _serial_right, const unsigned int _packetsize, const unsigned int _packetdelay)
{
    this->mac_address_left = this->create_MAC_from_char(_mac_ad_char_left);
    this->mac_address_right = this->create_MAC_from_char(_mac_ad_char_right);

    this->ip_address_left = this->create_IP_from_char(_ip_ad_char_left);
    this->ip_address_right = this->create_IP_from_char(_ip_ad_char_right);

    this->submask = this->create_IP_from_char(_submask);
    this->gateway = this->create_IP_from_char(_gateway);

    this->serial_left =_serial_left;
    this->serial_right = _serial_right;

    this->packetsize = _packetsize;
    this->packetdelay = _packetdelay;

}

Ini_Pgr_GigE_Stereo::~Ini_Pgr_GigE_Stereo()
{
    //ROS_INFO("Disconnecting the Cameras ....!!");

    this->error = this->left_cam.Disconnect();
    if (this->error != PGRERROR_OK)
    {
        PrintError(error);
	//ROS_ERROR("Error Disconnecting the Cameras!");
    }

    this->error = this->right_cam.Disconnect();
    if (this->error != PGRERROR_OK)
    {
        PrintError(error);
	//ROS_ERROR("Error Disconnecting the Cameras!");
    }



}



MACAddress Ini_Pgr_GigE_Stereo::create_MAC_from_char(const char * const mac_Address)
{

    unsigned int k = 0, l = 5, u= 0;

    unsigned char temp_mac_address [] = "000000000000";


    while(mac_Address[k])
    {
        if(mac_Address[k] != ':')
        {
            temp_mac_address[u] = mac_Address[k];
            u++;
        }

        ++k;
    }


    unsigned int mac_address_int [6] = {0};
    std::stringstream ss;
    int i = 11;
    unsigned int temp_var;
    while (i>=0 )
    {

        ss << std::hex << temp_mac_address[i-1] << temp_mac_address[i];
        ss >> temp_var ;
        mac_address_int[l] = temp_var;
        --l;
        i-= 2;
        ss.clear();
    }

    MACAddress mac_to_return;

    mac_to_return.octets[0] = (unsigned char)(mac_address_int[0]) & 0xFF;
    mac_to_return.octets[1] = (unsigned char)(mac_address_int[1]) & 0xFF;
    mac_to_return.octets[2] = (unsigned char)(mac_address_int[2]) & 0xFF;
    mac_to_return.octets[3] = (unsigned char)(mac_address_int[3]) & 0xFF;
    mac_to_return.octets[4] = (unsigned char)(mac_address_int[4]) & 0xFF;
    mac_to_return.octets[5] = (unsigned char)(mac_address_int[5]) & 0xFF;


    return mac_to_return;
}

IPAddress Ini_Pgr_GigE_Stereo::create_IP_from_char(const char * const ip_Address)
{
    unsigned int k = 0, l = 0, u= 0;

        unsigned char temp_ip_address [] = "000000000000";


        while(ip_Address[k])
        {
            if(ip_Address[k] != '.')
            {
                ++l;
            }
            else
            {
                switch(l)
                {
                case 0:
                    temp_ip_address[u+2] = ip_Address[k];
                    break;

                case 1:
                    temp_ip_address[u+2] = ip_Address[k-1];
                    break;

                case 2:
                    temp_ip_address[u+1] = ip_Address[k-2];
                    temp_ip_address[u+2] = ip_Address[k-1];
                    break;

                case 3:

                    temp_ip_address[u] =   ip_Address[k-3];
                    temp_ip_address[u+1] = ip_Address[k-2];
                    temp_ip_address[u+2] = ip_Address[k-1];
                    break;

                }

                l = 0;
                u +=3;

            }

            if(!ip_Address[k+1])
            {
                switch(l)
                {
                    case 0:
                        temp_ip_address[u+2] = ip_Address[k];
                        break;

                    case 1:
                        temp_ip_address[u+2] = ip_Address[k];
                        break;

                    case 2:
                        temp_ip_address[u+1] = ip_Address[k-1];
                        temp_ip_address[u+2] = ip_Address[k];
                        break;

                    case 3:

                        temp_ip_address[u] =   ip_Address[k-2];
                        temp_ip_address[u+1] = ip_Address[k-1];
                        temp_ip_address[u+2] = ip_Address[k];
                        break;
                }

            }
            ++k;
        }

        unsigned int ip_address_int = 0;
        int r = 0;

        for(int i = 11; i>=0; i=i-3)
        {
            int temp_var = 0;

            for(int o = i; o > (i-3); o--)
            {
                temp_var += ((int) (temp_ip_address[o]- 48)) * pow(10.0, i-o) ;
            }

            ip_address_int +=  (unsigned int) temp_var * pow(256.0 , r) ;
            ++r;

        }

        IPAddress ip_to_return;


        ip_to_return.octets[0] = (unsigned char)(ip_address_int >> 24) & 0xFF;
        ip_to_return.octets[1] = (unsigned char)(ip_address_int >> 16) & 0xFF;
        ip_to_return.octets[2] = (unsigned char)(ip_address_int >> 8) & 0xFF;
        ip_to_return.octets[3] = (unsigned char)(ip_address_int >> 0) & 0xFF;


        return ip_to_return;

}

bool Ini_Pgr_GigE_Stereo::initialize_pgr_gige_stereosystem()
{
    error;
    BusManager busmanager;


    unsigned int GigECamera_arraysize = 2;
    CameraInfo camerainfo [2];

    this->error = busmanager.DiscoverGigECameras(camerainfo , &GigECamera_arraysize);
    if (this->error != PGRERROR_OK)
    {
        //ROS_ERROR("Error discovering available cameras in the BUS system.");
        PrintError(error);
        return false;

    }

    if((camerainfo[0].serialNumber == this->serial_left || camerainfo[0].serialNumber == this->serial_right) && (camerainfo[1].serialNumber == this->serial_left || camerainfo[1].serialNumber == this->serial_right))
    {
        //switch cameras if swapped
        if(camerainfo[0].serialNumber == this->serial_left)
        {
            this->camerainfo_left = camerainfo[0];
            this->camerainfo_right = camerainfo[1];
        }
        else
        {
            this->camerainfo_left = camerainfo[1];
            this->camerainfo_right = camerainfo[0];
        }


        return true;

    }
    else
    {
        return false;
    }

}

bool Ini_Pgr_GigE_Stereo::force_ip_addresses()
{
    BusManager busmanager;

    if(this->camerainfo_left.serialNumber == this->serial_left && this->camerainfo_right.serialNumber == this->serial_right)
    {

            if(this->camerainfo_left.ipAddress != this->ip_address_left)
            {
               this->error = busmanager.ForceIPAddressToCamera(this->mac_address_left, this->ip_address_left, this->submask, this->gateway );
               if (error != PGRERROR_OK)
               {
                   //ROS_ERROR("Error forcing IP-Address to camera with sn: 12062824. \n");
                   PrintError(error);
                   return false;
               }
            }

            if(this->camerainfo_right.ipAddress != this->ip_address_right)
            {
               this->error = busmanager.ForceIPAddressToCamera(this->mac_address_right, this->ip_address_right, this->submask, this->gateway );
               if (this->error != PGRERROR_OK)
               {
                   //ROS_ERROR("Error forcing IP-Address to camera with sn: 12062828. \n");
                   PrintError(error);
                   return false;
               }
            }

        return true;

     }
     else
     {
        return false;
     }


}

bool Ini_Pgr_GigE_Stereo::setup_packet_transport()
{
    return this->setup_packet_transport(this->packetsize, this->packetdelay);
}

bool Ini_Pgr_GigE_Stereo::setup_packet_transport(const unsigned int _packetsize, const unsigned int _packetdelay)
{

    BusManager busmanager;
    this->error = busmanager.RescanBus();
    if (this->error != PGRERROR_OK)
    {
           //ROS_ERROR("Error rescanning BUS. \n");
           PrintError(error);
           return false;
    }



    this->error = busmanager.GetCameraFromSerialNumber(this->serial_left , & this->pgr_guid_left);
    if (this->error != PGRERROR_OK)
    {
        //ROS_ERROR("Error getting camera-pgr_guid from camera with sn: 12062824. \n");
        PrintError(error);
        return false;
    }

    this->error = busmanager.GetCameraFromSerialNumber(this->serial_right, & this->pgr_guid_right);
    if (this->error != PGRERROR_OK)
    {
        //ROS_ERROR("Error getting camera-pgr_guid from camera with sn: 12062828. \n");
        PrintError(error);
        return false;
    }


    this->error = this->left_cam.Connect(& this->pgr_guid_left);
    if (this->error != PGRERROR_OK)
    {
        //ROS_ERROR("Error trying to connect to camera with sn: 12062824. \n");
        PrintError(error);
        return false;
    }

    this->error = this->right_cam.Connect(& this->pgr_guid_right);
    if (this->error != PGRERROR_OK)
    {
        //ROS_ERROR("Error trying to connect to camera with sn: 12062828. \n");
        PrintError(error);
        return false;
    }


    GigEProperty prop_packetsize;
    prop_packetsize.propType = PACKET_SIZE;


    this->error = this->left_cam.GetGigEProperty(& prop_packetsize);
    if (this->error != PGRERROR_OK)
    {
        //ROS_ERROR("Error trying to connect to camera with sn: 12062828. \n");
        PrintError(error);
        return false;
    }

    if (prop_packetsize.value != _packetsize)
    {
        prop_packetsize.value = _packetsize;
        this->error = this->left_cam.SetGigEProperty(& prop_packetsize);
        if (this->error != PGRERROR_OK)
        {
            //ROS_ERROR("Error trying to connect to camera with sn: 12062828. \n");
            PrintError(error);
            return false;
        }

    }


    this->error = this->right_cam.GetGigEProperty(& prop_packetsize);
    if (this->error != PGRERROR_OK)
    {
        //ROS_ERROR("Error trying to connect to camera with sn: 12062828. \n");
        PrintError(error);
        return false;
    }

    if (prop_packetsize.value != _packetsize)
    {
        prop_packetsize.value = _packetsize;
        this->error = this->right_cam.SetGigEProperty(& prop_packetsize);
        if (this->error != PGRERROR_OK)
        {
            //ROS_ERROR("Error trying to connect to camera with sn: 12062828. \n");
            PrintError(error);
            return false;
        }

    }



    GigEProperty prop_packetdelay;
    prop_packetdelay.propType = PACKET_DELAY;


    this->error = this->left_cam.GetGigEProperty(& prop_packetdelay);
    if (this->error != PGRERROR_OK)
    {
        //ROS_ERROR("Error trying to connect to camera with sn: 12062828. \n");
        PrintError(error);
        return false;
    }

    if (prop_packetdelay.value != _packetdelay)
    {
        prop_packetdelay.value = _packetdelay;
        this->error = this->left_cam.SetGigEProperty(& prop_packetdelay);
        if (this->error != PGRERROR_OK)
        {
            //ROS_ERROR("Error trying to connect to camera with sn: 12062828. \n");
            PrintError(error);
            return false;
        }

    }


    this->error = this->right_cam.GetGigEProperty(& prop_packetdelay);
    if (this->error != PGRERROR_OK)
    {
        //ROS_ERROR("Error trying to connect to camera with sn: 12062828. \n");
        PrintError(error);
        return false;
    }

    if (prop_packetdelay.value != _packetdelay)
    {
        prop_packetdelay.value = _packetdelay;
        this->error = this->right_cam.SetGigEProperty(& prop_packetdelay);
        if (this->error != PGRERROR_OK)
        {
            //ROS_ERROR("Error trying to connect to camera with sn: 12062828. \n");
            PrintError(error);
            return false;
        }

    }

    this->packetsize = _packetsize;
    this->packetdelay = _packetdelay;

    return true;

}

void Ini_Pgr_GigE_Stereo::PrintError(Error error)
{
    error.PrintErrorTrace();
}

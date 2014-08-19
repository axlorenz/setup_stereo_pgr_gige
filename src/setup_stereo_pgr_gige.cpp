#include <ros/ros.h>
#include<iostream>
#include "FlyCapture2.h"
#include "ini_pgr_gige_stereo.h"

using namespace std;
using namespace FlyCapture2;


const string default_mac_left = "00:B0:9D:B8:10:68";
const string default_mac_right = "00:B0:9D:B8:10:6C";

const string default_ip_left = "192.168.4.2";
const string default_ip_right = "192.168.5.2";

const string  default_ip_submask = "255.255.255.0";
const string  default_ip_gateway =  "0.0.0.0";

const  int default_sn_left = 12062824;
const  int default_sn_right = 12062828;

const  int default_packetsize = 9000;
const  int default_packetdelay = 400;  


void PrintBuildInfo();
void PrintCameraInfo( CameraInfo pCamInfo );

int main(int argc, char** argv )

{

    	ros::init(argc, argv, "setup_stereo_pgr_gige");

  
    	ROS_INFO("The node tries to detect the two specified PointGrey cameras and sets them up with the given configuration: IP_Address and Package Size as well as Package Delay for each GigE camera. You need to have the FlyCap SDK installed for this node to work. \n");


    	ros::NodeHandle nh("~");

    	string mac_left;
    	string mac_right;

    	string ip_left;
    	string ip_right;

    	string  ip_submask;
    	string  ip_gateway;

    	int sn_left;
        int sn_right;

    	int packetsize;
    	int packetdelay;    


 	nh.param<string>("macaddress_left", mac_left, default_mac_left.c_str());
	nh.param<string>("macaddress_right", mac_right, default_mac_right.c_str() );

	nh.param<string>("ipaddress_left", ip_left, default_ip_left.c_str() );
	nh.param<string>("ipaddress_right", ip_right, default_ip_right.c_str() );

	nh.param<string>("ipaddress_submask", ip_submask, default_ip_submask.c_str());
	nh.param<string>("ipaddress_gateway", ip_gateway, default_ip_gateway.c_str());

	nh.param<int>("serial_left", sn_left, default_sn_left);
	nh.param<int>("serial_right", sn_right, default_sn_right);

	nh.param<int>("packetsize", packetsize, default_packetsize);
	nh.param<int>("packetdelay", packetdelay, default_packetdelay);


	ROS_INFO("macaddress left cam: %s .\n", mac_left.c_str());
	ROS_INFO("macaddress right cam: %s .\n", mac_right.c_str());

	ROS_INFO("ipaddress left cam: %s .\n", ip_left.c_str());
	ROS_INFO("ipaddress right cam : %s .\n", ip_right.c_str());

	ROS_INFO("ipaddress submask: %s .\n", ip_submask.c_str());
	ROS_INFO("ipaddress gateway: %s .\n", ip_gateway.c_str());

	ROS_INFO("serial no. left cam: %d .\n", sn_left);
	ROS_INFO("serial no. right cam : %d .\n", sn_right);

	ROS_INFO("packetsize: %d .\n", packetsize);
	ROS_INFO("packetdelay: %d .\n", packetdelay);
	

;

    	PrintBuildInfo();

   	Ini_Pgr_GigE_Stereo test_object ((const char* const) mac_left.c_str(), (const char* const) mac_right.c_str(), (const char* ) ip_left.c_str(), (const char* const) ip_right.c_str(), (const char* const) ip_submask.c_str(),(const char* const) ip_gateway.c_str(), (unsigned int) sn_left, (unsigned int) sn_right, (unsigned int) packetsize, (unsigned int) packetdelay);


	bool test_ini = test_object.initialize_pgr_gige_stereosystem();
	if(test_ini == false)
	{

		ROS_ERROR("Initialization Error. \n");
		return 0;
    	}
	else
	{
		ROS_INFO("Initialization successfull! \n");
		
		ROS_DEBUG("Info Left Camera: \n");	
		PrintCameraInfo( test_object.getCamerainfo_left());
		ROS_DEBUG("Info Right Camera: \n");
		PrintCameraInfo( test_object.getCamerainfo_right());


		bool force_ip = test_object.force_ip_addresses();
		if(force_ip == false)
		{
		    ROS_ERROR("IP Addresses cannot be forced! \n");
		}
		else
		{
		    ROS_INFO("IP Addresses have been successfully forced! \n");
		}

		bool transport = test_object.setup_packet_transport();
		if(transport == false)
		{              
		    ROS_ERROR("Package Size and Package Delay cannot be set. \n");
		}
		else
		{               
		    ROS_INFO("Package size and package delay have been set successfully! \n");
		}

		if(force_ip == true && transport == true)
			ROS_INFO("Setting up Pointgrey GigE stereo system was successfull! \n");

	}
	
    return 0;
}


void PrintBuildInfo()
{
    FC2Version fc2Version;
    Utilities::GetLibraryVersion( &fc2Version );
    char version[128];
    sprintf(
        version,
        "FlyCapture2 library version: %d.%d.%d.%d\n",
        fc2Version.major, fc2Version.minor, fc2Version.type, fc2Version.build );

    ROS_DEBUG( "%s", version );

    char timeStamp[512];
    sprintf( timeStamp, "Application build date: %s %s\n\n", __DATE__, __TIME__ );

    ROS_DEBUG( "%s", timeStamp );
}


void PrintCameraInfo( CameraInfo pCamInfo )
{
    ROS_DEBUG(
        "\n*** CAMERA INFORMATION ***\n"
        "Serial number - %u\n"
        "Camera model - %s\n"
        "Camera vendor - %s\n"
        "Sensor - %s\n"
        "Resolution - %s\n"
        "Firmware version - %s\n"
        "Firmware build time - %s\n\n",
        pCamInfo.serialNumber,
        pCamInfo.modelName,
        pCamInfo.vendorName,
        pCamInfo.sensorInfo,
        pCamInfo.sensorResolution,
        pCamInfo.firmwareVersion,
        pCamInfo.firmwareBuildTime );
}


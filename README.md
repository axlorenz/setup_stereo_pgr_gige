setup_stereo_pgr_gige
=====================

A ROS package for setting up a Pointgrey GigE stereo-camera system


The ROS node "setup_stereo_pgr_gige" tries to detect the two specified PointGrey cameras and sets them up with the given configuration: IP_Address and Package Size as well as Package Delay for each GigE camera. You need to have the FlyCap SDK installed for this node to work.

Parameters (all optional):

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
	
	
	
  const string default_mac_left = "00:B0:9D:B8:10:68";
  const string default_mac_right = "00:B0:9D:B8:10:6C";

  const string default_ip_left = "192.168.4.2";
  const string default_ip_right = "192.168.5.2";

  const string  default_ip_submask = "255.255.0.0";
  const string  default_ip_gateway =  "0.0.0.0";

  const  int default_sn_left = 12062824;
  const  int default_sn_right = 12062828;

  const  int default_packetsize = 9000;
  const  int default_packetdelay = 400;  


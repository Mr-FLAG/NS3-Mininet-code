/*
Title: DCN simulation using NS3
	Description: DCN Fat Tree Architecture for 16 servers is created. 
	Flow statistics and Packet capture files are generated. 
	Flow statistics files can be viewed in NetAnim.
	BY Flag in May, 2022.
*/

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/flow-monitor-helper.h"
#include <iostream>


using namespace ns3;
using namespace std;

NS_LOG_COMPONENT_DEFINE("DCNusingNS3");

int main(int argc, char *argv[])
{
	CommandLine cmd (__FILE__);
	cmd.Parse (argc, argv);
	  
	Time::SetResolution (Time::NS);
	LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
	LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
	Config::SetDefault("ns3::Ipv4GlobalRouting::RespondToInterfaceEvents", BooleanValue(true));
	
	PointToPointHelper Phy_Link;
	Phy_Link.SetDeviceAttribute ("DataRate", StringValue ("10Mbps"));
	Phy_Link.SetChannelAttribute ("Delay", StringValue ("20us"));
	

	NodeContainer pod0,pod1,pod2,pod3,pod4,pod5,core;
	pod0.Create (15);
	pod1.Create (15);
	pod2.Create (15);
	pod3.Create (15);
	pod4.Create (15);
	pod5.Create (15);
	core.Create (9);
	
	InternetStackHelper Stack;
	Stack.Install(pod0);
	Stack.Install(pod1);
	Stack.Install(pod2);
	Stack.Install(pod3);
	Stack.Install(pod4);
	Stack.Install(pod5);
	Stack.Install(core);
	
	//std::cout << "0" << std::endl;
	//Creating Topology
	NetDeviceContainer pod0_dev[18];
	for (int i = 0; i < 3; i ++){
		pod0_dev[i] = Phy_Link.Install(pod0.Get(i), pod0.Get(3));
		pod0_dev[i+3] = Phy_Link.Install(pod0.Get(i), pod0.Get(4));
		pod0_dev[i+6] = Phy_Link.Install(pod0.Get(i), pod0.Get(5));
		pod0_dev[i+9] = Phy_Link.Install(pod0.Get(3), pod0.Get(i+6));
		pod0_dev[i+12] = Phy_Link.Install(pod0.Get(4), pod0.Get(i+9));
		pod0_dev[i+15] = Phy_Link.Install(pod0.Get(5), pod0.Get(i+12));
	}

	NetDeviceContainer pod1_dev[18];
	for (int i = 0; i < 3; i ++){
		pod1_dev[i] = Phy_Link.Install(pod1.Get(i), pod1.Get(3));
		pod1_dev[i+3] = Phy_Link.Install(pod1.Get(i), pod1.Get(4));
		pod1_dev[i+6] = Phy_Link.Install(pod1.Get(i), pod1.Get(5));
		pod1_dev[i+9] = Phy_Link.Install(pod1.Get(3), pod1.Get(i+6));
		pod1_dev[i+12] = Phy_Link.Install(pod1.Get(4), pod1.Get(i+9));
		pod1_dev[i+15] = Phy_Link.Install(pod1.Get(5), pod1.Get(i+12));
	}

	NetDeviceContainer pod2_dev[18];
	for (int i = 0; i < 3; i ++){
		pod2_dev[i] = Phy_Link.Install(pod2.Get(i), pod2.Get(3));
		pod2_dev[i+3] = Phy_Link.Install(pod2.Get(i), pod2.Get(4));
		pod2_dev[i+6] = Phy_Link.Install(pod2.Get(i), pod2.Get(5));
		pod2_dev[i+9] = Phy_Link.Install(pod2.Get(3), pod2.Get(i+6));
		pod2_dev[i+12] = Phy_Link.Install(pod2.Get(4), pod2.Get(i+9));
		pod2_dev[i+15] = Phy_Link.Install(pod2.Get(5), pod2.Get(i+12));
	}
	//std::cout << "1" << std::endl;
	NetDeviceContainer pod3_dev[18];
	for (int i = 0; i < 3; i ++){
		pod3_dev[i] = Phy_Link.Install(pod3.Get(i), pod3.Get(3));
		pod3_dev[i+3] = Phy_Link.Install(pod3.Get(i), pod3.Get(4));
		pod3_dev[i+6] = Phy_Link.Install(pod3.Get(i), pod3.Get(5));
		pod3_dev[i+9] = Phy_Link.Install(pod3.Get(3), pod3.Get(i+6));
		pod3_dev[i+12] = Phy_Link.Install(pod3.Get(4), pod3.Get(i+9));
		pod3_dev[i+15] = Phy_Link.Install(pod3.Get(5), pod3.Get(i+12));
	}

	NetDeviceContainer pod4_dev[18];
	for (int i = 0; i < 3; i ++){
		pod4_dev[i] = Phy_Link.Install(pod4.Get(i), pod4.Get(3));
		pod4_dev[i+3] = Phy_Link.Install(pod4.Get(i), pod4.Get(4));
		pod4_dev[i+6] = Phy_Link.Install(pod4.Get(i), pod4.Get(5));
		pod4_dev[i+9] = Phy_Link.Install(pod4.Get(3), pod4.Get(i+6));
		pod4_dev[i+12] = Phy_Link.Install(pod4.Get(4), pod4.Get(i+9));
		pod4_dev[i+15] = Phy_Link.Install(pod4.Get(5), pod4.Get(i+12));
	}

	NetDeviceContainer pod5_dev[18];
	for (int i = 0; i < 3; i ++){
		pod5_dev[i] = Phy_Link.Install(pod5.Get(i), pod5.Get(3));
		pod5_dev[i+3] = Phy_Link.Install(pod5.Get(i), pod5.Get(4));
		pod5_dev[i+6] = Phy_Link.Install(pod5.Get(i), pod5.Get(5));
		pod5_dev[i+9] = Phy_Link.Install(pod5.Get(3), pod5.Get(i+6));
		pod5_dev[i+12] = Phy_Link.Install(pod5.Get(4), pod5.Get(i+9));
		pod5_dev[i+15] = Phy_Link.Install(pod5.Get(5), pod5.Get(i+12));
	}	

	
	//Core router connections
	NetDeviceContainer core_dev[54];
	for (int i = 0; i < 9; i ++){
		core_dev[i] = Phy_Link.Install(core.Get(i), pod0.Get(i/3));
		core_dev[i+9] = Phy_Link.Install(core.Get(i), pod1.Get(i/3));
		core_dev[i+18] = Phy_Link.Install(core.Get(i), pod2.Get(i/3));
		core_dev[i+27] = Phy_Link.Install(core.Get(i), pod3.Get(i/3));
		core_dev[i+36] = Phy_Link.Install(core.Get(i), pod4.Get(i/3));
		core_dev[i+45] = Phy_Link.Install(core.Get(i), pod5.Get(i/3));
	}
		
	//Assigning the IP address
	Ipv4AddressHelper address;
	Ipv4InterfaceContainer pod0_Iface[18];//0,pod0_Iface1,pod0_Iface2,pod0_Iface3,pod0_Iface4,pod0_Iface5,pod0_Iface6,pod0_Iface7;
	address.SetBase("10.0.0.0","255.255.255.0");
	for(int i = 0; i < 18; i ++){
		pod0_Iface[i] = address.Assign (pod0_dev[i]);	
	}
	
	Ipv4InterfaceContainer pod1_Iface[18];//,pod1_Iface1,pod1_Iface2,pod1_Iface3,pod1_Iface4,pod1_Iface5,pod1_Iface6,pod1_Iface7;
	address.SetBase("20.0.0.0","255.255.255.0");
	for(int i = 0; i < 18; i ++){
		pod1_Iface[i] = address.Assign (pod1_dev[i]);	
	}
	
	Ipv4InterfaceContainer pod2_Iface[18];//0,pod2_Iface1,pod2_Iface2,pod2_Iface3,pod2_Iface4,pod2_Iface5,pod2_Iface6,pod2_Iface7;
	address.SetBase("30.0.0.0","255.255.255.0");
	for(int i = 0; i < 18; i ++){
		pod2_Iface[i] = address.Assign (pod2_dev[i]);	
	}
	
	Ipv4InterfaceContainer pod3_Iface[18];
	address.SetBase("40.0.0.0","255.255.255.0");
	for(int i = 0; i < 18; i ++){
		pod3_Iface[i] = address.Assign (pod3_dev[i]);	
	}

	Ipv4InterfaceContainer pod4_Iface[18];
	address.SetBase("50.0.0.0","255.255.255.0");
	for(int i = 0; i < 18; i ++){
		pod4_Iface[i] = address.Assign (pod4_dev[i]);	
	}

	Ipv4InterfaceContainer pod5_Iface[18];
	address.SetBase("60.0.0.0","255.255.255.0");
	for(int i = 0; i < 18; i ++){
		pod5_Iface[i] = address.Assign(pod5_dev[i]);	
	}
	
	//Core router Ifaces
	Ipv4InterfaceContainer core_Iface[54];	
	address.SetBase("70.0.0.0","255.255.255.0");
	for(int i = 0; i < 54; i ++){
		core_Iface[i] = address.Assign(core_dev[i]);	
	}
	
	//Routing tables
	Ipv4GlobalRoutingHelper:: PopulateRoutingTables();
	
	//Udp Applications
	// UdpEchoServerHelper echoServer (6666);
	// ApplicationContainer serverApps0,serverApps1;//,serverApps2,serverApps3
	// serverApps0 = echoServer.Install (pod5.Get(14));
	// serverApps0.Start (Seconds (1.0));
	// serverApps0.Stop (Seconds (3.0));
	
	// ApplicationContainer clientApp0, clientApp1;//, clientApp2, clientApp3
	// UdpEchoClientHelper echoClient (pod5_Iface[9].GetAddress (1), 6666);
	// echoClient.SetAttribute ("MaxPackets", UintegerValue (10));
	// echoClient.SetAttribute ("Interval", TimeValue (NanoSeconds (800)));
	// echoClient.SetAttribute ("PacketSize", UintegerValue (100));
	
	// clientApp0 = echoClient.Install (pod0.Get (14));
	// clientApp0.Start (Seconds (1.5));
	// clientApp0.Stop (Seconds (2.5));

	// serverApps1 = echoServer.Install (pod5.Get(6));
	// serverApps1.Start (Seconds (1.0));
	// serverApps1.Stop (Seconds (3.0));

	// UdpEchoClientHelper echoClient2 (pod5_Iface[9].GetAddress (1), 6666);
	// echoClient2.SetAttribute ("MaxPackets", UintegerValue (10));
	// echoClient2.SetAttribute ("Interval", TimeValue (NanoSeconds (800)));
	// echoClient2.SetAttribute ("PacketSize", UintegerValue (100));

	// clientApp1 = echoClient2.Install (pod0.Get (14));
	// clientApp1.Start (Seconds (1.5));
	// clientApp1.Stop (Seconds (2.5));


/*
	serverApps2 = echoServer.Install (pod5.Get(14));
	serverApps3 = echoServer.Install (pod5.Get(14));
	serverApps2.Start (Seconds (1.0));
	serverApps2.Stop (Seconds (3.0));
	serverApps3.Start (Seconds (1.0));
	serverApps3.Stop (Seconds (3.0));
	UdpEchoClientHelper echoClient3 (pod5_Iface[17].GetAddress (1), 6666);
	echoClient3.SetAttribute ("MaxPackets", UintegerValue (10));
	echoClient3.SetAttribute ("Interval", TimeValue (NanoSeconds (800)));
	echoClient3.SetAttribute ("PacketSize", UintegerValue (100));

	UdpEchoClientHelper echoClient4 (pod5_Iface[17].GetAddress (1), 6666);
	echoClient4.SetAttribute ("MaxPackets", UintegerValue (10));
	echoClient4.SetAttribute ("Interval", TimeValue (NanoSeconds (800)));
	echoClient4.SetAttribute ("PacketSize", UintegerValue (100));

	clientApp2 = echoClient3.Install (pod1.Get (6));
	clientApp3 = echoClient4.Install (pod1.Get (6));
	clientApp2.Start (Seconds (1.5));
	clientApp2.Stop (Seconds (2.5));
	clientApp3.Start (Seconds (1.5));
	clientApp3.Stop (Seconds (2.5));
	*/

	Ipv4StaticRoutingHelper staticR;
	Ptr<Ipv4> B = (pod1.Get(5))->GetObject<Ipv4> ();
	Ptr<Ipv4StaticRouting> staticRB = staticR.GetStaticRouting (B);
	staticRB->AddHostRouteTo (Ipv4Address ("60.0.0.36"), Ipv4Address ("20.0.0.17"), 3);
  	staticRB->AddHostRouteTo (Ipv4Address ("60.0.0.34"), Ipv4Address ("20.0.0.15"), 2);
	


	Ptr<Ipv4> C = (pod5.Get(5))->GetObject<Ipv4> ();
	Ptr<Ipv4StaticRouting> staticRC = staticR.GetStaticRouting (C);
  	staticRC->AddHostRouteTo (Ipv4Address ("60.0.0.34"), Ipv4Address ("60.0.0.34"), 5);
  	staticRC->AddHostRouteTo (Ipv4Address ("60.0.0.32"), Ipv4Address ("60.0.0.32"), 4);
	
	//tcp flow
	int tcpSegmentSize = 1000; 
	uint32_t maxBytes = 10000; // 0 means "unlimited"
	Config::SetDefault ("ns3::TcpSocket::SegmentSize", UintegerValue (tcpSegmentSize));
	//Config::SetDefault ("ns3::TcpSocket::DelAckCount", UintegerValue (0)); 
	int port0 = 80; 
	PacketSinkHelper sink0 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny(), port0)); 
	ApplicationContainer sinkApp0 = sink0.Install (pod5.Get(14)); 
	sinkApp0.Start (Seconds (1)); 
	sinkApp0.Stop (Seconds (2.5));

	BulkSendHelper sourceAhelper0 ("ns3::TcpSocketFactory", InetSocketAddress("60.0.0.36", port0));
	sourceAhelper0.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper0.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	ApplicationContainer sourceAppsA0 = sourceAhelper0.Install (pod1.Get (14));
	sourceAppsA0.Start (Seconds (1.5));
	sourceAppsA0.Stop (Seconds (2.5));


	int port1 = 90; 
	PacketSinkHelper sink1 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny(), port1)); 
	ApplicationContainer sinkApp1 = sink1.Install (pod5.Get(13)); 
	sinkApp1.Start (Seconds (1)); 
	sinkApp1.Stop (Seconds (2.5));

	BulkSendHelper sourceAhelper1 ("ns3::TcpSocketFactory", InetSocketAddress("60.0.0.34", port1));
	sourceAhelper1.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper1.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	ApplicationContainer sourceAppsA1 = sourceAhelper1.Install (pod1.Get (14));
	sourceAppsA1.Start (Seconds (1.5));
	sourceAppsA1.Stop (Seconds (2.5));

	int port2 = 92; 
	PacketSinkHelper sink2 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny(), port2)); 
	ApplicationContainer sinkApp2 = sink2.Install (pod5.Get(12)); 
	sinkApp2.Start (Seconds (1)); 
	sinkApp2.Stop (Seconds (2.5));

	BulkSendHelper sourceAhelper2 ("ns3::TcpSocketFactory", InetSocketAddress("60.0.0.32", port2));
	sourceAhelper2.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper2.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	ApplicationContainer sourceAppsA2 = sourceAhelper2.Install (pod1.Get (14));
	sourceAppsA2.Start (Seconds (1.5));
	sourceAppsA2.Stop (Seconds (2.5));

	// int port1 = 90; 
	// PacketSinkHelper sink1 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny(), port1)); 
	// ApplicationContainer sinkApp1 = sink1.Install (pod5.Get(13)); 
	// sinkApp1.Start (Seconds (1)); 
	// sinkApp1.Stop (Seconds (2.5));

	// BulkSendHelper sourceAhelper1 ("ns3::TcpSocketFactory", InetSocketAddress("60.0.0.34", port1));
	// sourceAhelper1.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	// sourceAhelper1.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	// ApplicationContainer sourceAppsA1 = sourceAhelper1.Install (pod1.Get (14));
	// sourceAppsA1.Start (Seconds (1.5));
	// sourceAppsA1.Stop (Seconds (2.5));

	RipHelper show_help;
	Ptr<OutputStreamWrapper> routingStream = Create<OutputStreamWrapper> (&std::cout);
	show_help.PrintRoutingTableAt(Seconds(1.0), pod1.Get(5), routingStream);

	//Phy_Link.EnablePcapAll ("FatTree");
	//Phy_Link.EnablePcapAll("DCN_FatTree_Pcap");
		/*
	//Flow Statstics
	FlowMonitorHelper flowmonHelper;
	flowmonHelper.InstallAll();
*/
	//Animation, use ./NetAnim to open the software, then select "animation.xml" to open the animation.
	AnimationInterface anim ("6ary_animation.xml");
	anim.SetConstantPosition(pod0.Get(0), 10, 75);
	anim.SetConstantPosition(pod0.Get(1), 20, 75);
	anim.SetConstantPosition(pod0.Get(2), 30, 75);
	anim.SetConstantPosition(pod0.Get(3), 10, 125);
	anim.SetConstantPosition(pod0.Get(4), 20, 125);
	anim.SetConstantPosition(pod0.Get(5), 30, 125);
	anim.SetConstantPosition(pod0.Get(6), 7, 175);
	anim.SetConstantPosition(pod0.Get(7), 10, 175);
	anim.SetConstantPosition(pod0.Get(8), 13, 175);
	anim.SetConstantPosition(pod0.Get(9), 17, 175);
	anim.SetConstantPosition(pod0.Get(10), 20, 175);
	anim.SetConstantPosition(pod0.Get(11), 23, 175);
	anim.SetConstantPosition(pod0.Get(12), 27, 175);
	anim.SetConstantPosition(pod0.Get(13), 30, 175);
	anim.SetConstantPosition(pod0.Get(14), 33, 175);
	
	anim.SetConstantPosition(pod1.Get(0), 42, 75);
	anim.SetConstantPosition(pod1.Get(1), 52, 75);
	anim.SetConstantPosition(pod1.Get(2), 62, 75);
	anim.SetConstantPosition(pod1.Get(3), 42, 125);
	anim.SetConstantPosition(pod1.Get(4), 52, 125);
	anim.SetConstantPosition(pod1.Get(5), 62, 125);
	anim.SetConstantPosition(pod1.Get(6), 39, 175);
	anim.SetConstantPosition(pod1.Get(7), 42, 175);
	anim.SetConstantPosition(pod1.Get(8), 45, 175);
	anim.SetConstantPosition(pod1.Get(9), 49, 175);
	anim.SetConstantPosition(pod1.Get(10), 52, 175);
	anim.SetConstantPosition(pod1.Get(11), 55, 175);
	anim.SetConstantPosition(pod1.Get(12), 59, 175);
	anim.SetConstantPosition(pod1.Get(13), 62, 175);
	anim.SetConstantPosition(pod1.Get(14), 65, 175);

	
	//NodeTo
	anim.SetConstantPosition(pod2.Get(0), 74, 75);
	anim.SetConstantPosition(pod2.Get(1), 84, 75);
	anim.SetConstantPosition(pod2.Get(2), 94, 75);
	anim.SetConstantPosition(pod2.Get(3), 74, 125);
	anim.SetConstantPosition(pod2.Get(4), 84, 125);
	anim.SetConstantPosition(pod2.Get(5), 94, 125);
	anim.SetConstantPosition(pod2.Get(6), 71, 175);
	anim.SetConstantPosition(pod2.Get(7), 74, 175);
	anim.SetConstantPosition(pod2.Get(8), 77, 175);
	anim.SetConstantPosition(pod2.Get(9), 81, 175);
	anim.SetConstantPosition(pod2.Get(10), 84, 175);
	anim.SetConstantPosition(pod2.Get(11), 87, 175);
	anim.SetConstantPosition(pod2.Get(12), 91, 175);
	anim.SetConstantPosition(pod2.Get(13), 94, 175);
	anim.SetConstantPosition(pod2.Get(14), 97, 175);
	
	
	anim.SetConstantPosition(pod3.Get(0), 106, 75);
	anim.SetConstantPosition(pod3.Get(1), 116, 75);
	anim.SetConstantPosition(pod3.Get(2), 126, 75);
	anim.SetConstantPosition(pod3.Get(3), 106, 125);
	anim.SetConstantPosition(pod3.Get(4), 116, 125);
	anim.SetConstantPosition(pod3.Get(5), 126, 125);
	anim.SetConstantPosition(pod3.Get(6), 103, 175);
	anim.SetConstantPosition(pod3.Get(7), 106, 175);
	anim.SetConstantPosition(pod3.Get(8), 109, 175);
	anim.SetConstantPosition(pod3.Get(9), 113, 175);
	anim.SetConstantPosition(pod3.Get(10), 116, 175);
	anim.SetConstantPosition(pod3.Get(11), 119, 175);
	anim.SetConstantPosition(pod3.Get(12), 123, 175);
	anim.SetConstantPosition(pod3.Get(13), 126, 175);
	anim.SetConstantPosition(pod3.Get(14), 129, 175);

	anim.SetConstantPosition(pod4.Get(0), 138, 75);
	anim.SetConstantPosition(pod4.Get(1), 148, 75);
	anim.SetConstantPosition(pod4.Get(2), 158, 75);
	anim.SetConstantPosition(pod4.Get(3), 138, 125);
	anim.SetConstantPosition(pod4.Get(4), 148, 125);
	anim.SetConstantPosition(pod4.Get(5), 158, 125);
	anim.SetConstantPosition(pod4.Get(6), 135, 175);
	anim.SetConstantPosition(pod4.Get(7), 138, 175);
	anim.SetConstantPosition(pod4.Get(8), 141, 175);
	anim.SetConstantPosition(pod4.Get(9), 145, 175);
	anim.SetConstantPosition(pod4.Get(10), 148, 175);
	anim.SetConstantPosition(pod4.Get(11), 151, 175);
	anim.SetConstantPosition(pod4.Get(12), 155, 175);
	anim.SetConstantPosition(pod4.Get(13), 158, 175);
	anim.SetConstantPosition(pod4.Get(14), 161, 175);

	anim.SetConstantPosition(pod5.Get(0), 170, 75);
	anim.SetConstantPosition(pod5.Get(1), 180, 75);
	anim.SetConstantPosition(pod5.Get(2), 190, 75);
	anim.SetConstantPosition(pod5.Get(3), 170, 125);
	anim.SetConstantPosition(pod5.Get(4), 180, 125);
	anim.SetConstantPosition(pod5.Get(5), 190, 125);
	anim.SetConstantPosition(pod5.Get(6), 167, 175);
	anim.SetConstantPosition(pod5.Get(7), 170, 175);
	anim.SetConstantPosition(pod5.Get(8), 173, 175);
	anim.SetConstantPosition(pod5.Get(9), 177, 175);
	anim.SetConstantPosition(pod5.Get(10), 180, 175);
	anim.SetConstantPosition(pod5.Get(11), 183, 175);
	anim.SetConstantPosition(pod5.Get(12), 187, 175);
	anim.SetConstantPosition(pod5.Get(13), 190, 175);
	anim.SetConstantPosition(pod5.Get(14), 193, 175);
	
	anim.SetConstantPosition(core.Get(0), 25, 25);
	anim.SetConstantPosition(core.Get(1), 45, 25);
	anim.SetConstantPosition(core.Get(2), 65, 25);
	anim.SetConstantPosition(core.Get(3), 85, 25);
	anim.SetConstantPosition(core.Get(4), 105, 25);
	anim.SetConstantPosition(core.Get(5), 125, 25);
	anim.SetConstantPosition(core.Get(6), 145, 25);
	anim.SetConstantPosition(core.Get(7), 165, 25);
	anim.SetConstantPosition(core.Get(8), 185, 25);

	anim.SetStartTime(Seconds(0.0));
	anim.SetStopTime(Seconds(2.0));

	Simulator::Stop (Seconds (2.0));
	Simulator::Run ();
  	NS_LOG_INFO ("Running the Simulation.");
	//This SericalToXmlFile must be set after Simulator::Run().
	//flowmonHelper.SerializeToXmlFile ("DCN_FatTree_FlowStat.flowmon", true, true);
  	NS_LOG_INFO ("Flowmon file creating.");
  	NS_LOG_INFO ("Done.");
	Simulator::Destroy ();

	return 0;

}

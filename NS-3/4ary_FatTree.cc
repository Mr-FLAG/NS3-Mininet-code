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


using namespace ns3;
using namespace std;

static void
Change (uint32_t old_value, uint32_t new_value)
{
  NS_LOG_UNCOND (Simulator::Now ().GetSeconds ()*2 << "\t" << new_value);
}

NS_LOG_COMPONENT_DEFINE("DCNusingNS3");

int main(int argc, char *argv[])
{
	CommandLine cmd (__FILE__);
	cmd.Parse (argc, argv);
	  
	Time::SetResolution (Time::NS);
	LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
	LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);

	Config::SetDefault ("ns3::TcpL4Protocol::SocketType", StringValue ("ns3::TcpNewReno"));
  	Config::SetDefault ("ns3::TcpSocket::InitialCwnd", UintegerValue (1));
	
	PointToPointHelper Phy_Link;
	Phy_Link.SetDeviceAttribute ("DataRate", StringValue ("10Mbps"));
	Phy_Link.SetChannelAttribute ("Delay", StringValue ("15us"));
	

	NodeContainer pod0,pod1,pod2,pod3,core;
	pod0.Create (8);
	pod1.Create (8);
	pod2.Create (8);
	pod3.Create (8);
	core.Create (4);

	// Ipv4ListRoutingHelper list;
	// Ipv4GlobalRoutingHelper globalR;
	// Ipv4StaticRoutingHelper staticR;
	// list.Add(staticR, 20);
	// list.Add(globalR, 10);
	
	InternetStackHelper Stack;
	//Stack.SetRoutingHelper(list);
	Stack.Install(pod1);
	Stack.Install(pod2);
	Stack.Install(pod3);
	Stack.Install(core);
	Stack.Install(pod0);
	
	
	//Creating Topology
	NetDeviceContainer pod0_dev0,pod0_dev1,pod0_dev2,pod0_dev3,pod0_dev4,pod0_dev5,pod0_dev6,pod0_dev7;
	pod0_dev0 = Phy_Link.Install(pod0.Get(0), pod0.Get(4));
	pod0_dev1 = Phy_Link.Install(pod0.Get(1), pod0.Get(4));
	pod0_dev2 = Phy_Link.Install(pod0.Get(2), pod0.Get(5));
	pod0_dev3 = Phy_Link.Install(pod0.Get(3), pod0.Get(5));
	pod0_dev4 = Phy_Link.Install(pod0.Get(4), pod0.Get(6));
	pod0_dev5 = Phy_Link.Install(pod0.Get(4), pod0.Get(7));
	pod0_dev6 = Phy_Link.Install(pod0.Get(5), pod0.Get(6));
	pod0_dev7 = Phy_Link.Install(pod0.Get(5), pod0.Get(7));
	
	NetDeviceContainer pod1_dev0,pod1_dev1,pod1_dev2,pod1_dev3,pod1_dev4,pod1_dev5,pod1_dev6,pod1_dev7;
	pod1_dev0 = Phy_Link.Install(pod1.Get(0), pod1.Get(4));
	pod1_dev1 = Phy_Link.Install(pod1.Get(1), pod1.Get(4));
	pod1_dev2 = Phy_Link.Install(pod1.Get(2), pod1.Get(5));
	pod1_dev3 = Phy_Link.Install(pod1.Get(3), pod1.Get(5));
	pod1_dev4 = Phy_Link.Install(pod1.Get(4), pod1.Get(6));
	pod1_dev5 = Phy_Link.Install(pod1.Get(4), pod1.Get(7));
	pod1_dev6 = Phy_Link.Install(pod1.Get(5), pod1.Get(6));
	pod1_dev7 = Phy_Link.Install(pod1.Get(5), pod1.Get(7));
	
	NetDeviceContainer pod2_dev0,pod2_dev1,pod2_dev2,pod2_dev3,pod2_dev4,pod2_dev5,pod2_dev6,pod2_dev7;
	pod2_dev0 = Phy_Link.Install(pod2.Get(0), pod2.Get(4));
	pod2_dev1 = Phy_Link.Install(pod2.Get(1), pod2.Get(4));
	pod2_dev2 = Phy_Link.Install(pod2.Get(2), pod2.Get(5));
	pod2_dev3 = Phy_Link.Install(pod2.Get(3), pod2.Get(5));
	pod2_dev4 = Phy_Link.Install(pod2.Get(4), pod2.Get(6));
	pod2_dev5 = Phy_Link.Install(pod2.Get(4), pod2.Get(7));
	pod2_dev6 = Phy_Link.Install(pod2.Get(5), pod2.Get(6));
	pod2_dev7 = Phy_Link.Install(pod2.Get(5), pod2.Get(7));
	
	NetDeviceContainer pod3_dev0,pod3_dev1,pod3_dev2,pod3_dev3,pod3_dev4,pod3_dev5,pod3_dev6,pod3_dev7;
	pod3_dev0 = Phy_Link.Install(pod3.Get(0), pod3.Get(4));
	pod3_dev1 = Phy_Link.Install(pod3.Get(1), pod3.Get(4));
	pod3_dev2 = Phy_Link.Install(pod3.Get(2), pod3.Get(5));
	pod3_dev3 = Phy_Link.Install(pod3.Get(3), pod3.Get(5));
	pod3_dev4 = Phy_Link.Install(pod3.Get(4), pod3.Get(6));
	pod3_dev5 = Phy_Link.Install(pod3.Get(4), pod3.Get(7));
	pod3_dev6 = Phy_Link.Install(pod3.Get(5), pod3.Get(6));
	pod3_dev7 = Phy_Link.Install(pod3.Get(5), pod3.Get(7));
	

	//Core router connections
	NetDeviceContainer core_dev0,core_dev1,core_dev2,core_dev3,core_dev4,core_dev5,core_dev6,core_dev7;
	NetDeviceContainer core_dev8,core_dev9,core_dev10,core_dev11,core_dev12,core_dev13,core_dev14,core_dev15;
	core_dev0 = Phy_Link.Install(pod0.Get(6), core.Get(0));
	core_dev1 = Phy_Link.Install(pod1.Get(6), core.Get(0));
	core_dev2 = Phy_Link.Install(pod2.Get(6), core.Get(0));
	core_dev3 = Phy_Link.Install(pod3.Get(6), core.Get(0));
	
	core_dev4 = Phy_Link.Install(pod0.Get(6), core.Get(1));
	core_dev5 = Phy_Link.Install(pod1.Get(6), core.Get(1));
	core_dev6 = Phy_Link.Install(pod2.Get(6), core.Get(1));
	core_dev7 = Phy_Link.Install(pod3.Get(6), core.Get(1));
	
	core_dev8 = Phy_Link.Install(pod0.Get(7), core.Get(2));
	core_dev9 = Phy_Link.Install(pod1.Get(7), core.Get(2));
	core_dev10 = Phy_Link.Install(pod2.Get(7), core.Get(2));
	core_dev11 = Phy_Link.Install(pod3.Get(7), core.Get(2));
	
	core_dev12 = Phy_Link.Install(pod0.Get(7), core.Get(3));
	core_dev13 = Phy_Link.Install(pod1.Get(7), core.Get(3));
	core_dev14 = Phy_Link.Install(pod2.Get(7), core.Get(3));
	core_dev15 = Phy_Link.Install(pod3.Get(7), core.Get(3));
		
	//Assigning the IP address
	Ipv4AddressHelper address;
	Ipv4InterfaceContainer pod0_Iface0,pod0_Iface1,pod0_Iface2,pod0_Iface3,
							pod0_Iface4,pod0_Iface5,pod0_Iface6,pod0_Iface7;
	address.SetBase("10.0.0.0","255.255.255.0");
	pod0_Iface0 = address.Assign (pod0_dev0);
	
	address.SetBase("10.0.1.0","255.255.255.0");
	pod0_Iface1 = address.Assign(pod0_dev1);
	
	address.SetBase("10.0.2.0","255.255.255.0");
	pod0_Iface2 = address.Assign(pod0_dev2);
	
	address.SetBase("10.0.3.0","255.255.255.0");
	pod0_Iface3 = address.Assign(pod0_dev3);
	
	address.SetBase("10.1.0.0","255.255.0.0");
	pod0_Iface4 = address.Assign(pod0_dev4);

	address.SetBase("10.2.0.0","255.255.0.0");
	pod0_Iface5 = address.Assign(pod0_dev5);

	address.SetBase("10.1.1.0","255.255.255.0");
	pod0_Iface6 = address.Assign(pod0_dev6);

	address.SetBase("10.2.1.0","255.255.255.0");
	pod0_Iface7 = address.Assign(pod0_dev7);
	
	Ipv4InterfaceContainer pod1_Iface0,pod1_Iface1,pod1_Iface2,pod1_Iface3,pod1_Iface4,pod1_Iface5,pod1_Iface6,pod1_Iface7;
	address.SetBase("20.0.0.0","255.255.255.0");
	pod1_Iface0 = address.Assign (pod1_dev0);
	
	address.SetBase("20.0.1.0","255.255.255.0");
	pod1_Iface1 = address.Assign(pod1_dev1);
	
	address.SetBase("20.0.2.0","255.255.255.0");
	pod1_Iface2 = address.Assign(pod1_dev2);
	
	address.SetBase("20.0.3.0","255.255.255.0");
	pod1_Iface3 = address.Assign(pod1_dev3);
	
	address.SetBase("20.1.0.0","255.255.0.0");
	pod1_Iface4 = address.Assign(pod1_dev4);

	address.SetBase("20.2.0.0","255.255.0.0");
	pod1_Iface5 = address.Assign(pod1_dev5);

	address.SetBase("20.1.1.0","255.255.255.0");
	pod1_Iface6 = address.Assign(pod1_dev6);

	address.SetBase("20.2.1.0","255.255.255.0");
	pod1_Iface7 = address.Assign(pod1_dev7);
	
	Ipv4InterfaceContainer pod2_Iface0,pod2_Iface1,pod2_Iface2,pod2_Iface3,pod2_Iface4,pod2_Iface5,pod2_Iface6,pod2_Iface7;
	address.SetBase("30.0.0.0","255.255.255.0");
	pod2_Iface0 = address.Assign (pod2_dev0);
	
	address.SetBase("30.0.1.0","255.255.255.0");
	pod2_Iface1 = address.Assign(pod2_dev1);
	
	address.SetBase("30.0.2.0","255.255.255.0");
	pod2_Iface2 = address.Assign(pod2_dev2);
	
	address.SetBase("30.0.3.0","255.255.255.0");
	pod2_Iface3 = address.Assign(pod2_dev3);

	address.SetBase("30.1.0.0","255.255.0.0");
	pod2_Iface4 = address.Assign(pod2_dev4);

	address.SetBase("30.2.0.0","255.255.0.0");
	pod2_Iface5 = address.Assign(pod2_dev5);

	address.SetBase("30.1.1.0","255.255.255.0");
	pod2_Iface6 = address.Assign(pod2_dev6);

	address.SetBase("30.2.1.0","255.255.255.0");
	pod2_Iface7 = address.Assign(pod2_dev7);
	
	Ipv4InterfaceContainer pod3_Iface0,pod3_Iface1,pod3_Iface2,pod3_Iface3,pod3_Iface4,pod3_Iface5,pod3_Iface6,pod3_Iface7;
	address.SetBase("40.0.0.0","255.255.255.0");
	pod3_Iface0 = address.Assign (pod3_dev0);
	
	address.SetBase("40.0.1.0","255.255.255.0");
	pod3_Iface1 = address.Assign(pod3_dev1);
	
	address.SetBase("40.0.2.0","255.255.255.0");
	pod3_Iface2 = address.Assign(pod3_dev2);
	
	address.SetBase("40.0.3.0","255.255.255.0");
	pod3_Iface3 = address.Assign(pod3_dev3);
	
	address.SetBase("40.1.0.0","255.255.0.0");
	pod3_Iface4 = address.Assign(pod3_dev4);

	address.SetBase("40.2.0.0","255.255.0.0");
	pod3_Iface5 = address.Assign(pod3_dev5);

	address.SetBase("40.1.1.0","255.255.255.0");
	pod3_Iface6 = address.Assign(pod3_dev6);

	address.SetBase("40.2.1.0","255.255.255.0");
	pod3_Iface7 = address.Assign(pod3_dev7);
	
	//Core router Ifaces
	Ipv4InterfaceContainer core_Iface0,core_Iface1,core_Iface2,core_Iface3,core_Iface4,core_Iface5,core_Iface6,core_Iface7;
	Ipv4InterfaceContainer core_Iface8,core_Iface9,core_Iface10,core_Iface11,core_Iface12,core_Iface13,core_Iface14,core_Iface15;
	
	address.SetBase("50.1.1.0","255.255.255.0");
	core_Iface0 = address.Assign(core_dev0);

	address.SetBase("50.1.2.0","255.255.255.0");
	core_Iface1 = address.Assign(core_dev1);

	address.SetBase("50.1.3.0","255.255.255.0");
	core_Iface2 = address.Assign(core_dev2);

	address.SetBase("50.1.4.0","255.255.255.0");
	core_Iface3 = address.Assign(core_dev3);
	
	address.SetBase("50.2.1.0","255.255.255.0");
	core_Iface4 = address.Assign(core_dev4);

	address.SetBase("50.2.2.0","255.255.255.0");
	core_Iface5 = address.Assign(core_dev5);

	address.SetBase("50.2.3.0","255.255.255.0");
	core_Iface6 = address.Assign(core_dev6);

	address.SetBase("50.2.4.0","255.255.255.0");
	core_Iface7 = address.Assign(core_dev7);
	
	address.SetBase("50.3.1.0","255.255.255.0");
	core_Iface8 = address.Assign(core_dev8);

	address.SetBase("50.3.2.0","255.255.255.0");
	core_Iface9 = address.Assign(core_dev9);

	address.SetBase("50.3.3.0","255.255.255.0");
	core_Iface10 = address.Assign(core_dev10);

	address.SetBase("50.3.4.0","255.255.255.0");
	core_Iface11 = address.Assign(core_dev11);
	
	address.SetBase("50.4.1.0","255.255.255.0");
	core_Iface12 = address.Assign(core_dev12);

	address.SetBase("50.4.2.0","255.255.255.0");
	core_Iface13 = address.Assign(core_dev13);

	address.SetBase("50.4.3.0","255.255.255.0");
	core_Iface14 = address.Assign(core_dev14);

	address.SetBase("50.4.4.0","255.255.255.0");
	core_Iface15 = address.Assign(core_dev15);
	
	//Routing tables
	
	Ipv4GlobalRoutingHelper:: PopulateRoutingTables();
	/*
	Ptr<Ipv4> A = (pod3.Get(6))->GetObject<Ipv4> ();
	Ptr<Ipv4StaticRouting> staticRoutingA = staticR.GetStaticRouting (A);
  	staticRoutingA->AddHostRouteTo(Ipv4Address ("10.0.0.1"), Ipv4Address ("50.2.4.2"), 4);
	*/
	


	/* //show flow table:
	RipHelper show_help;
	Ptr<OutputStreamWrapper> routingStream = Create<OutputStreamWrapper> (&std::cout);
	show_help.PrintRoutingTableAt(Seconds(1.0), pod3.Get(4), routingStream);
	*/
	
	// Ipv4StaticRoutingHelper staticR;
	// Ptr<Ipv4> B = (pod3.Get(4))->GetObject<Ipv4> ();
	// Ptr<Ipv4StaticRouting> staticRB = staticR.GetStaticRouting (B);
  	// staticRB->AddHostRouteTo (Ipv4Address ("10.0.0.1"), Ipv4Address ("40.2.0.2"), 4);


	// //Udp Applications
	// UdpEchoServerHelper echoServer (4444);
	// ApplicationContainer serverApps0,serverApps1,serverApps2,serverApps3;
	// serverApps0 = echoServer.Install (pod0.Get(0));
	// serverApps0.Start (Seconds (1.0));
	// serverApps0.Stop (Seconds (3.0));
	
	// serverApps1 = echoServer.Install (pod0.Get(1));
	// serverApps1.Start (Seconds (1.0));
	// serverApps1.Stop (Seconds (5.0));
	
	
	// ApplicationContainer clientApp0, clientApp1, clientApp2, clientApp3;
	// UdpEchoClientHelper echoClient (pod0_Iface0.GetAddress (0), 4444);
	// echoClient.SetAttribute ("MaxPackets", UintegerValue (10));
	// echoClient.SetAttribute ("Interval", TimeValue (NanoSeconds (800)));
	// echoClient.SetAttribute ("PacketSize", UintegerValue (100));
	// clientApp0 = echoClient.Install (pod3.Get (0));
	
	// UdpEchoClientHelper echoClient2 (pod0_Iface1.GetAddress (0), 4444);
	// echoClient2.SetAttribute ("MaxPackets", UintegerValue (10));
	// echoClient2.SetAttribute ("Interval", TimeValue (NanoSeconds (800)));
	// echoClient2.SetAttribute ("PacketSize", UintegerValue (100));
	// clientApp1 = echoClient2.Install (pod3.Get (0));
	
	// clientApp0.Start (Seconds (1.5));
	// clientApp0.Stop (Seconds (2.0));
	// clientApp1.Start (Seconds (1.5));
	// clientApp1.Stop (Seconds (2.5));

	
	// serverApps2 = echoServer.Install (pod1.Get(0));
	// serverApps3 = echoServer.Install (pod1.Get(1));

	// serverApps2.Start (Seconds (1.0));
	// serverApps2.Stop (Seconds (5.0));
	// serverApps3.Start (Seconds (1.0));
	// serverApps3.Stop (Seconds (5.0));

	// UdpEchoClientHelper echoClient3 (pod1_Iface0.GetAddress (0), 9);
	// echoClient3.SetAttribute ("MaxPackets", UintegerValue (10));
	// echoClient3.SetAttribute ("Interval", TimeValue (NanoSeconds (800)));
	// echoClient3.SetAttribute ("PacketSize", UintegerValue (100));
	// clientApp2 = echoClient3.Install (pod2.Get (2));

	// UdpEchoClientHelper echoClient4 (pod1_Iface1.GetAddress (0), 9);
	// echoClient4.SetAttribute ("MaxPackets", UintegerValue (10));
	// echoClient4.SetAttribute ("Interval", TimeValue (NanoSeconds (800)));
	// echoClient4.SetAttribute ("PacketSize", UintegerValue (100));
	// clientApp3 = echoClient4.Install (pod2.Get (3));
	
	// clientApp2.Start (Seconds (1.5));
	// clientApp2.Stop (Seconds (2.5));
	// clientApp3.Start (Seconds (1.5));
	// clientApp3.Stop (Seconds (2.5));
	

	int tcpSegmentSize = 1024; 
	uint32_t maxBytes = 1024*100; // 0 means "unlimited"
	Config::SetDefault ("ns3::TcpSocket::SegmentSize", UintegerValue (tcpSegmentSize));
	//Config::SetDefault ("ns3::TcpSocket::DelAckCount", UintegerValue (0)); 
	int port0 = 80; 
	PacketSinkHelper sink0 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), port0)); 
	ApplicationContainer sinkApp0 = sink0.Install (pod3.Get(0)); 
	sinkApp0.Start (Seconds (1)); 
	sinkApp0.Stop (Seconds (2.5));

	//Ptr<Socket> TcpSocket = Socket::CreateSocket (pod0.Get (0), TcpSocketFactory::GetTypeId ());
	BulkSendHelper sourceAhelper0 ("ns3::TcpSocketFactory", InetSocketAddress(pod3_Iface0.GetAddress(0), port0));
	sourceAhelper0.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper0.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	// TcpSocket.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	// TcpSocket.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize));
	ApplicationContainer sourceAppsA0 = sourceAhelper0.Install (pod0.Get (0));
	sourceAppsA0.Start (Seconds (1.5));
	sourceAppsA0.Stop (Seconds (2.5));

	//sourceAppsA0.TraceConnectWithoutContext ("CongestionWindow", MakeCallback (&Change));

	// int port1 = 90; 
	// PacketSinkHelper sink1 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), port1)); 
	// ApplicationContainer sinkApp1 = sink1.Install (pod0.Get(1)); 
	// sinkApp1.Start (Seconds (1)); 
	// sinkApp1.Stop (Seconds (2.5));

	// BulkSendHelper sourceAhelper1 ("ns3::TcpSocketFactory", InetSocketAddress(pod0_Iface1.GetAddress(0), port1));
	// sourceAhelper1.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	// sourceAhelper1.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	// ApplicationContainer sourceAppsA1 = sourceAhelper1.Install (pod3.Get (0));
	// sourceAppsA1.Start (Seconds (1.5));
	// sourceAppsA1.Stop (Seconds (2.5));
	/*
	//tcp flow
	int tcpSegmentSize = 1000; 
	uint32_t maxBytes = 10000; // 0 means "unlimited"
	Config::SetDefault ("ns3::TcpSocket::SegmentSize", UintegerValue (tcpSegmentSize));
	//Config::SetDefault ("ns3::TcpSocket::DelAckCount", UintegerValue (0)); 
	int port0 = 80,port1 = 90; 
	PacketSinkHelper sink0 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), port0)); 
	PacketSinkHelper sink1 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), port1));
	PacketSinkHelper sink2 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), port0)); 
	PacketSinkHelper sink3 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), port1)); 		
	ApplicationContainer sinkApp0 = sink0.Install (pod0.Get(2)); 
	ApplicationContainer sinkApp1 = sink1.Install (pod0.Get(3)); 
	ApplicationContainer sinkApp2 = sink2.Install (pod1.Get(0)); 
	ApplicationContainer sinkApp3 = sink3.Install (pod1.Get(1)); 
	sinkApp0.Start (Seconds (1)); 
	sinkApp0.Stop (Seconds (2.5));
	sinkApp1.Start (Seconds (1)); 
	sinkApp1.Stop (Seconds (2.5));
	sinkApp2.Start (Seconds (1)); 
	sinkApp2.Stop (Seconds (2.5));
	sinkApp3.Start (Seconds (1)); 
	sinkApp3.Stop (Seconds (2.5));
 
	BulkSendHelper sourceAhelper0 ("ns3::TcpSocketFactory", InetSocketAddress(pod0_Iface2.GetAddress (0), port0));
	BulkSendHelper sourceAhelper1 ("ns3::TcpSocketFactory", InetSocketAddress(pod0_Iface3.GetAddress (0), port1)); 
	BulkSendHelper sourceAhelper2 ("ns3::TcpSocketFactory", InetSocketAddress(pod1_Iface0.GetAddress (0), port0));
	OnOffHelper sourceAhelper3 ("ns3::TcpSocketFactory", InetSocketAddress(pod1_Iface1.GetAddress (0), port1)); 
	
	sourceAhelper0.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper0.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper1.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper1.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	sourceAhelper2.SetAttribute ("MaxBytes", UintegerValue (maxBytes)); 
	sourceAhelper2.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	//sourceAhelper3.SetAttribute ("SendSize", UintegerValue (tcpSegmentSize)); 
	//
	sourceAhelper3.SetAttribute ("OnTime", StringValue ("ns3::ConstantRandomVariable[Constant=1]"));  
    sourceAhelper3.SetAttribute ("OffTime", StringValue ("ns3::ConstantRandomVariable[Constant=1]"));
	sourceAhelper3.SetAttribute ("PacketSize", UintegerValue (1000));
    sourceAhelper3.SetAttribute ("DataRate", StringValue("1Mb/s")); 
	// 
	ApplicationContainer sourceAppsA0 = sourceAhelper0.Install (pod3.Get (0)); 
	ApplicationContainer sourceAppsA1 = sourceAhelper1.Install (pod3.Get (3)); 
	ApplicationContainer sourceAppsA2 = sourceAhelper2.Install (pod2.Get (2)); 
	ApplicationContainer sourceAppsA3 = sourceAhelper3.Install (pod2.Get (3)); 
	sourceAppsA0.Start (Seconds (1.5));
	sourceAppsA0.Stop (Seconds (2.5));
	sourceAppsA1.Start (Seconds (1.5));
	sourceAppsA1.Stop (Seconds (2.5));
	sourceAppsA2.Start (Seconds (1.5));
	sourceAppsA2.Stop (Seconds (2.5));
	sourceAppsA3.Start (Seconds (1.5));
	sourceAppsA3.Stop (Seconds (2.5));*/
	
	
	//Phy_Link.EnablePcapAll ("FatTree");
	//Phy_Link.EnablePcapAll("DCN_FatTree_Pcap");
		
	//Flow Statstics
	FlowMonitorHelper flowmonHelper;
	flowmonHelper.InstallAll();

	//Animation, use ./NetAnim to open the software, then select "animation.xml" to open the animation.
	AnimationInterface anim ("animation.xml");
	anim.SetConstantPosition(pod0.Get(0), 10, 200);
	anim.SetConstantPosition(pod0.Get(1), 20, 200);
	anim.SetConstantPosition(pod0.Get(2), 30, 200);
	anim.SetConstantPosition(pod0.Get(3), 40, 200);
	anim.SetConstantPosition(pod0.Get(4), 15, 160);
	anim.SetConstantPosition(pod0.Get(5), 35, 160);
	anim.SetConstantPosition(pod0.Get(6), 15, 120);
	anim.SetConstantPosition(pod0.Get(7), 35, 120);
	
	anim.SetConstantPosition(pod1.Get(0), 60, 200);
	anim.SetConstantPosition(pod1.Get(1), 70, 200);
	anim.SetConstantPosition(pod1.Get(2), 80, 200);
	anim.SetConstantPosition(pod1.Get(3), 90, 200);
	anim.SetConstantPosition(pod1.Get(4), 65, 160);
	anim.SetConstantPosition(pod1.Get(5), 85, 160);
	anim.SetConstantPosition(pod1.Get(6), 65, 120);
	anim.SetConstantPosition(pod1.Get(7), 85, 120);
	
	//NodeTo
	anim.SetConstantPosition(pod2.Get(0), 110, 200);
	anim.SetConstantPosition(pod2.Get(1), 120, 200);
	anim.SetConstantPosition(pod2.Get(2), 130, 200);
	anim.SetConstantPosition(pod2.Get(3), 140, 200);
	anim.SetConstantPosition(pod2.Get(4), 115, 160);
	anim.SetConstantPosition(pod2.Get(5), 135, 160);
	anim.SetConstantPosition(pod2.Get(6), 115, 120);
	anim.SetConstantPosition(pod2.Get(7), 135, 120);
	
	anim.SetConstantPosition(pod3.Get(0), 160, 200);
	anim.SetConstantPosition(pod3.Get(1), 170, 200);
	anim.SetConstantPosition(pod3.Get(2), 180, 200);
	anim.SetConstantPosition(pod3.Get(3), 190, 200);
	anim.SetConstantPosition(pod3.Get(4), 165, 160);
	anim.SetConstantPosition(pod3.Get(5), 185, 160);
	anim.SetConstantPosition(pod3.Get(6), 165, 120);
	anim.SetConstantPosition(pod3.Get(7), 185, 120);
	
	anim.SetConstantPosition(core.Get(0), 25, 70);
	anim.SetConstantPosition(core.Get(1), 75, 70);
	anim.SetConstantPosition(core.Get(2), 125, 70);
	anim.SetConstantPosition(core.Get(3), 175, 70);
	anim.SetStartTime(Seconds(0.0));
	anim.SetStopTime(Seconds(2.0));

	Simulator::Stop (Seconds (2.0));
	Simulator::Run ();
  	NS_LOG_INFO ("Running the Simulation.");
	//This SericalToXmlFile must be set after Simulator::Run().
	flowmonHelper.SerializeToXmlFile ("DCN_FatTree_FlowStat.flowmon", true, true);
  	NS_LOG_INFO ("Flowmon file creating.");
  	NS_LOG_INFO ("Done.");
	Simulator::Destroy ();

	return 0;

}

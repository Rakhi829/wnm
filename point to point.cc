None selected

Skip to content
Using NMAM Institute Of Technology Mail with screen readers

11 of 1,497
Fwd:
Inbox

NNM24CC027 MANASWI H V <nnm24cc027@nmamit.in>
Attachments
Sun, Nov 15, 12:44 PM (1 day ago)
to me



---------- Forwarded message ---------
From: NNM24CC027 MANASWI H V <nnm24cc027@nmamit.in>
Date: Fri, Nov 13, 2026 at 10:20 AM
Subject: Fwd:
To: <nnm24cc030@nmamit.in>




---------- Forwarded message ---------
From: NNM24CC039 POOJARY VISHESH GANESH <nnm24cc039@nmamit.in>
Date: Fri, Sep 11, 2026 at 10:12 AM
Subject:
To: <nnm24cc040@nmamit.in>, <nnm24cc027@nmamit.in>




 3 Attachments
  •  Scanned by Gmail
PointToPoint.cc
100%
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("PointToPoint");

int main(int argc, char *argv[])
{
	CommandLine cmd(__FILE__);
	cmd.Parse(argc,argv);
	
	Time::SetResolution(Time::NS);
	LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
	LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);
	
	NodeContainer nodes;
	nodes.Create(2);
	PointToPointHelper p2p;
    	p2p.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
    	p2p.SetChannelAttribute("Delay", StringValue("2ms"));
    	
	NetDeviceContainer devices = p2p.Install(nodes);

    	InternetStackHelper stack;
    	stack.Install(nodes);
	Ipv4AddressHelper address;
    	address.SetBase("10.1.1.0", "255.255.255.0");
    	
	Ipv4InterfaceContainer interfaces =address.Assign(devices);
	
	UdpEchoServerHelper echoServer(8080);
	
	ApplicationContainer serverApps = echoServer.Install(nodes.Get(1));

    	serverApps.Start(Seconds(1.0));
    	serverApps.Stop(Seconds(20.0));
    	
    	UdpEchoClientHelper echoClient(interfaces.GetAddress(1),8080);
	echoClient.SetAttribute("MaxPackets",UintegerValue(10));
	echoClient.SetAttribute("Interval",TimeValue(Seconds(1.0)));
	echoClient.SetAttribute("PacketSize",UintegerValue(1024));
	
	ApplicationContainer clientApps =echoClient.Install(nodes.Get(0));
	clientApps.Start(Seconds(2.0));
	clientApps.Stop(Seconds(20.0));
	
	AsciiTraceHelper ascciTraceHelper;
	p2p.EnableAsciiAll(ascciTraceHelper.CreateFileStream("1024.tr"));
	
	AnimationInterface anim("p2p.xml");
	
	Simulator::Run();
	Simulator::Destroy();
	return 0;
	
}
Displaying goodput.txt.

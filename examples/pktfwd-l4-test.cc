#include "stdlib.h"
#include "fstream"
#include <sstream>
#include <list>
#include <map>
#include <cstring>

#include "ns3/uinteger.h"
#include "ns3/core-module.h"
#include "ns3/simulator-module.h"
#include "ns3/node-module.h"
#include "ns3/pktfwd-norm-prov-module.h"
#include "ns3/rapidnet-module.h"
#include "ns3/values-module.h"
#include "ns3/helper-module.h"

#include "ns3/csma-helper.h"
#include "ns3/ipv4-address-helper.h"
#include "ns3/ipv4-address.h"

//#include "pktfwd-utility.h"

#include "ns3/l4-platform-helper.h"

/* Device identification*/
#define device(host, dvtype)\
  tuple(PktfwdNormProv::DEVICE,\
  attr("device_attr1", Ipv4Value, host),  \
  attr("device_attr2", Int32Value, dvtype))

#define insert_device(host, dvtype)                                            \
  app(host) -> Insert(device(addr(host), dvtype));


/* Links Connecting Hosts To switches*/
#define linkhr(host, sw)\
  tuple(PktfwdNormProv::LINKHR,\
  attr("linkhr_attr1", Ipv4Value, host),  \
  attr("linkhr_attr2", Ipv4Value, sw))

#define insert_linkhr(host, sw)                                            \
  app(host) -> Insert(linkhr(addr(host), addr(sw)));

/* Links connecting switches to other devices*/
#define link(sw, nei)\
  tuple(PktfwdNormProv::LINK,\
  attr("link_attr1", Ipv4Value, sw),  \
  attr("link_attr2", Ipv4Value, nei))

#define insert_link(sw, nei)                                            \
  app(sw) -> Insert(link(addr(sw), addr(nei)));

/* Input packets */
#define initpacket(host, srcadd, dstadd, data)               \
  tuple(PktfwdNormProv::INITPACKET,\
  attr("initPacket_attr1", Ipv4Value, host),  \
  attr("initPacket_attr2", Ipv4Value, srcadd), \
  attr("initPacket_attr3", Ipv4Value, dstadd),    \
  attr("initPacket_attr4", StrValue, data))

#define insert_packet(host, srcadd, dstadd, data)                            \
  app(host) -> Insert(initpacket(addr(host), addr(srcadd), addr(dstadd), data));


/* flow entry */
#define flowentry(sw, dst, next)		\
  tuple(PktfwdNormProv::FLOWENTRY,\
	attr("flowEntry_attr1", Ipv4Value, sw),\
	attr("flowEntry_attr2", Ipv4Value, dst),         \
	attr("flowEntry_attr3", Ipv4Value, next))

#define insert_flowentry(sw, dst, next)				\
  app(sw) -> Insert(flowentry(addr(sw), addr(dst), addr(next)))

#define SWITCH 0
#define HOST 1
#define HOSTPERSWC 1 //Warning: This is not changeable under the current routing algorithm
#define DEFAULT_PKTNUM 20

using namespace std;
using namespace ns3;
using namespace ns3::rapidnet;
using namespace ns3::rapidnet::pktfwdnormprov;

ApplicationContainer apps;


string dstLocSpec ="";
string localPort = "";


void AddLink(int src,int dst)
{
  app(src)->Insert (link (src, dest));
}

int main()
{
  // Use realtime simulator
  GlobalValue::Bind ("SimulatorImplementationType",
		     StringValue ("ns3::RealtimeSimulatorImpl"));

  LogComponentEnable("Pingpong", LOG_LEVEL_INFO);
  LogComponentEnable("RapidNetApplicationBase", LOG_LEVEL_INFO);

  uint16_t port;

  CommandLine cmd;
  cmd.AddValue ("dest", "Destination LocSpec IP:Port", destLocSpec);
  cmd.AddValue ("localPort", "Local RapidNet port", localPort);
  cmd.Parse (argc, argv);

  if (localPort != "")
    {
      std::istringstream sin (localPort);
      sin >> port;
    } 
  else 
    {
      port = 11111;
    }
 
  // Install L4-Platform
  NodeContainer nodeContainer;
  nodeContainer.Create (1);
  nodeContainer.Create (2);
  L4PlatformHelper platform;
  platform.Install (nodeContainer);
  PktfwdNormProvHelper helper = PktfwdNormProvHelper ();
  helper.SetL4Platform (true);
  helper.SetAttribute ("RapidNetPort", UintegerValue (port));
  
  apps = helper.Install (nodeContainer);

  ofstream* decorator_out = InstallDecorator(apps, ".", 2000, 2000);

  // Set default value
  if (destLocSpec == "")
    destLocSpec = app (1)->GetLocalLocSpec ();

  apps.Start (Seconds (0.0));
  apps.Stop (Seconds (50.0));

  schedule (0.0001, AddLink);

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
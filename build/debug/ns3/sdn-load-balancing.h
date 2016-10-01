/* A RapidNet application. Generated by RapidNet compiler. */

#ifndef SDNLOADBALANCING_H
#define SDNLOADBALANCING_H

#include <string>
#include <iostream>
#include "ns3/ptr.h"
#include "ns3/event-id.h"
#include "ns3/ipv4-address.h"
#include "ns3/rapidnet-header.h"
#include "ns3/relation-base.h"
#include "ns3/database.h"
#include "ns3/rapidnet-application-base.h"
#include "ns3/aggregator.h"
#include "ns3/aggwrap.h"

using namespace std;
using namespace ns3;

namespace ns3 {

class Socket;
class Packet;

namespace rapidnet {
namespace sdnloadbalancing {

class SdnLoadBalancing : public RapidNetApplicationBase
{
public:
  static const string DESIGNATED;
  static const string HASHED;
  static const string INITPACKET;
  static const string PACKET;
  static const string RECVPACKET;
  static const string SERVERMAPPING;

  static TypeId GetTypeId (void);

  SdnLoadBalancing ();

  virtual ~SdnLoadBalancing ();

protected:

  virtual void DoDispose (void);

  virtual void StartApplication (void);

  virtual void StopApplication (void);

  virtual void InitDatabase (void);

  virtual void DemuxRecv (Ptr<Tuple> tuple);

  virtual void R1Eca0Ins (Ptr<Tuple> initPacket);

  virtual void R2_eca (Ptr<Tuple> packet);

  virtual void R3_eca (Ptr<Tuple> hashed);

  virtual void R4_eca (Ptr<Tuple> packet);

};

} // namespace sdnloadbalancing
} // namespace rapidnet
} // namespace ns3

#endif // SDNLOADBALANCING_H

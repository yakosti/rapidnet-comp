/* A RapidNet application. Generated by RapidNet compiler. */

#ifndef PKTFWDNORM_H
#define PKTFWDNORM_H

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
namespace pktfwdnorm {

class PktfwdNorm : public RapidNetApplicationBase
{
public:
  static const string DEVICE;
  static const string EPRETURN;
  static const string EPROVQUERY;
  static const string ERRETURN;
  static const string ERULEQUERY;
  static const string EPACKET;
  static const string EPACKETDELETE;
  static const string EPACKETTEMP;
  static const string EPACKETTEMPDELETE;
  static const string ERECVPACKET;
  static const string ERECVPACKETDELETE;
  static const string ERECVPACKETTEMP;
  static const string ERECVPACKETTEMPDELETE;
  static const string FLOWENTRY;
  static const string INITPACKET;
  static const string LINK;
  static const string LINKHR;
  static const string PITERATE;
  static const string PQLIST;
  static const string PRESULTTMP;
  static const string PRETURN;
  static const string PACKET;
  static const string PACKETDELETE;
  static const string PROV;
  static const string PROVQUERY;
  static const string RITERATE;
  static const string RQLIST;
  static const string RRESULTTMP;
  static const string RRETURN;
  static const string RECVPACKET;
  static const string RULEEXEC;
  static const string RULEQUERY;

  static TypeId GetTypeId (void);

  PktfwdNorm ();

  virtual ~PktfwdNorm ();

protected:

  virtual void DoDispose (void);

  virtual void StartApplication (void);

  virtual void StopApplication (void);

  virtual void InitDatabase (void);

  virtual void DemuxRecv (Ptr<Tuple> tuple);

  virtual void Prov_rs1_1_ecaAdd (Ptr<Tuple> packet);

  virtual void Prov_rs1_1_ecaDel (Ptr<Tuple> packetDelete);

  virtual void Prov_rs1_2_ecaAdd (Ptr<Tuple> epacketTemp);

  virtual void Prov_rs1_2_ecaDel (Ptr<Tuple> epacketTempDelete);

  virtual void Prov_rs1_3_ecaAdd (Ptr<Tuple> epacketTemp);

  virtual void Prov_rs1_3_ecaDel (Ptr<Tuple> epacketTempDelete);

  virtual void Prov_rs1_4_ecaAdd (Ptr<Tuple> epacket);

  virtual void Prov_rs1_4_ecaDel (Ptr<Tuple> epacketDelete);

  virtual void Prov_rs1_5_ecaAdd (Ptr<Tuple> epacket);

  virtual void Prov_rs1_5_ecaDel (Ptr<Tuple> epacketDelete);

  virtual void Prov_rh1_1Eca0Ins (Ptr<Tuple> device);

  virtual void Prov_rh1_1Eca0Del (Ptr<Tuple> device);

  virtual void Prov_rh1_1Eca3Ins (Ptr<Tuple> initPacket);

  virtual void Prov_rh1_1Eca3Del (Ptr<Tuple> initPacket);

  virtual void Prov_rh1_1Eca7Ins (Ptr<Tuple> linkhr);

  virtual void Prov_rh1_1Eca7Del (Ptr<Tuple> linkhr);

  virtual void Prov_rh2_1_ecaAdd (Ptr<Tuple> packet);

  virtual void Prov_rh2_1_ecaDel (Ptr<Tuple> packetDelete);

  virtual void Prov_rh2_2_ecaAdd (Ptr<Tuple> erecvPacketTemp);

  virtual void Prov_rh2_2_ecaDel (Ptr<Tuple> erecvPacketTempDelete);

  virtual void Prov_rh2_3_ecaAdd (Ptr<Tuple> erecvPacketTemp);

  virtual void Prov_rh2_3_ecaDel (Ptr<Tuple> erecvPacketTempDelete);

  virtual void Prov_rh2_4_ecaAdd (Ptr<Tuple> erecvPacket);

  virtual void Prov_rh2_4_ecaDel (Ptr<Tuple> erecvPacketDelete);

  virtual void Prov_rh2_5_ecaAdd (Ptr<Tuple> erecvPacket);

  virtual void Prov_rh2_5_ecaDel (Ptr<Tuple> erecvPacketDelete);

  virtual void Prov_edb_1Eca1Ins (Ptr<Tuple> device);

  virtual void Prov_edb_1Eca1Del (Ptr<Tuple> device);

  virtual void Prov_edb_2Eca1Ins (Ptr<Tuple> flowEntry);

  virtual void Prov_edb_2Eca1Del (Ptr<Tuple> flowEntry);

  virtual void Prov_edb_3Eca1Ins (Ptr<Tuple> initPacket);

  virtual void Prov_edb_3Eca1Del (Ptr<Tuple> initPacket);

  virtual void Prov_edb_4Eca1Ins (Ptr<Tuple> link);

  virtual void Prov_edb_4Eca1Del (Ptr<Tuple> link);

  virtual void Prov_edb_5Eca1Ins (Ptr<Tuple> linkhr);

  virtual void Prov_edb_5Eca1Del (Ptr<Tuple> linkhr);

  virtual void Edb1_eca (Ptr<Tuple> provQuery);

  virtual void Idb1_eca (Ptr<Tuple> provQuery);

  virtual void Idb2_eca (Ptr<Tuple> provQuery);

  virtual void Idb3_eca (Ptr<Tuple> provQuery);

  virtual void Idb4_eca (Ptr<Tuple> pIterate);

  virtual void Idb5_eca (Ptr<Tuple> pIterate);

  virtual void Idb6_eca (Ptr<Tuple> eRuleQuery);

  virtual void Idb7_eca (Ptr<Tuple> rReturn);

  virtual void Idb8Eca0Ins (Ptr<Tuple> pResultTmp);

  virtual void Idb8Eca1Ins (Ptr<Tuple> pQList);

  virtual void Idb9_eca (Ptr<Tuple> ePReturn);

  virtual void Rv1_eca (Ptr<Tuple> ruleQuery);

  virtual void Rv2_eca (Ptr<Tuple> ruleQuery);

  virtual void Rv3_eca (Ptr<Tuple> ruleQuery);

  virtual void Rv4_eca (Ptr<Tuple> rIterate);

  virtual void Rv5_eca (Ptr<Tuple> rIterate);

  virtual void Rv6_eca (Ptr<Tuple> eProvQuery);

  virtual void Rv7_eca (Ptr<Tuple> pReturn);

  virtual void Rv8Eca0Ins (Ptr<Tuple> rResultTmp);

  virtual void Rv8Eca1Ins (Ptr<Tuple> rQList);

  virtual void Rv9_eca (Ptr<Tuple> eRReturn);

};

} // namespace pktfwdnorm
} // namespace rapidnet
} // namespace ns3

#endif // PKTFWDNORM_H

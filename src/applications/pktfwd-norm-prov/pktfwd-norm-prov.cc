/* A RapidNet application. Generated by RapidNet compiler. */

#include "pktfwd-norm-prov.h"
#include <cstdlib>
#include "ns3/nstime.h"
#include "ns3/simulator.h"
#include "ns3/type-ids.h"
#include "ns3/rapidnet-types.h"
#include "ns3/rapidnet-utils.h"
#include "ns3/assignor.h"
#include "ns3/selector.h"
#include "ns3/rapidnet-functions.h"

using namespace std;
using namespace ns3;
using namespace ns3::rapidnet;
using namespace ns3::rapidnet::pktfwdnormprov;

const string PktfwdNormProv::DEVICE = "device";
const string PktfwdNormProv::EPACKET = "epacket";
const string PktfwdNormProv::EPACKETTEMP = "epacketTemp";
const string PktfwdNormProv::ERECVPACKET = "erecvPacket";
const string PktfwdNormProv::ERECVPACKETTEMP = "erecvPacketTemp";
const string PktfwdNormProv::FLOWENTRY = "flowEntry";
const string PktfwdNormProv::INITPACKET = "initPacket";
const string PktfwdNormProv::LINK = "link";
const string PktfwdNormProv::LINKHR = "linkhr";
const string PktfwdNormProv::PACKET = "packet";
const string PktfwdNormProv::PROV = "prov";
const string PktfwdNormProv::RECVPACKET = "recvPacket";
const string PktfwdNormProv::RULEEXEC = "ruleExec";

NS_LOG_COMPONENT_DEFINE ("PktfwdNormProv");
NS_OBJECT_ENSURE_REGISTERED (PktfwdNormProv);

TypeId
PktfwdNormProv::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::rapidnet::pktfwdnormprov::PktfwdNormProv")
    .SetParent<RapidNetApplicationBase> ()
    .AddConstructor<PktfwdNormProv> ()
    ;
  return tid;
}

PktfwdNormProv::PktfwdNormProv()
{
  NS_LOG_FUNCTION_NOARGS ();
}

PktfwdNormProv::~PktfwdNormProv()
{
  NS_LOG_FUNCTION_NOARGS ();
}

void
PktfwdNormProv::DoDispose (void)
{
  NS_LOG_FUNCTION_NOARGS ();

  RapidNetApplicationBase::DoDispose ();
}

void
PktfwdNormProv::StartApplication (void)
{
  NS_LOG_FUNCTION_NOARGS ();

  RapidNetApplicationBase::StartApplication ();
  RAPIDNET_LOG_INFO("PktfwdNormProv Application Started");
}

void
PktfwdNormProv::StopApplication ()
{
  NS_LOG_FUNCTION_NOARGS ();

  RapidNetApplicationBase::StopApplication ();
  RAPIDNET_LOG_INFO("PktfwdNormProv Application Stopped");
}

void
PktfwdNormProv::InitDatabase ()
{
  //RapidNetApplicationBase::InitDatabase ();

  AddRelationWithKeys (DEVICE, attrdeflist (
    attrdef ("device_attr2", INT32)));

  AddRelationWithKeys (FLOWENTRY, attrdeflist (
    attrdef ("flowEntry_attr2", IPV4)));

  AddRelationWithKeys (INITPACKET, attrdeflist (
    attrdef ("initPacket_attr2", IPV4),
    attrdef ("initPacket_attr3", IPV4),
    attrdef ("initPacket_attr4", STR)));

  AddRelationWithKeys (LINK, attrdeflist (
    attrdef ("link_attr2", IPV4)));

  AddRelationWithKeys (LINKHR, attrdeflist (
    attrdef ("linkhr_attr2", IPV4)));

  AddRelationWithKeys (RECVPACKET, attrdeflist (
    attrdef ("recvPacket_attr2", IPV4),
    attrdef ("recvPacket_attr3", IPV4),
    attrdef ("recvPacket_attr4", STR)));

  AddRelationWithKeys (RULEEXEC, attrdeflist (
    attrdef ("ruleExec_attr4", LIST)));

}

void
PktfwdNormProv::DemuxRecv (Ptr<Tuple> tuple)
{
  RapidNetApplicationBase::DemuxRecv (tuple);

  if (IsRecvEvent (tuple, PACKET))
    {
      Prov_rs1_1_eca (tuple);
    }
  if (IsRecvEvent (tuple, EPACKETTEMP))
    {
      Prov_rs1_2_eca (tuple);
    }
  if (IsRecvEvent (tuple, EPACKETTEMP))
    {
      Prov_rs1_3_eca (tuple);
    }
  if (IsRecvEvent (tuple, EPACKET))
    {
      Prov_rs1_4_eca (tuple);
    }
  if (IsRecvEvent (tuple, EPACKET))
    {
      Prov_rs1_5_eca (tuple);
    }
  if (IsInsertEvent (tuple, DEVICE))
    {
      Prov_rh1_1Eca0Ins (tuple);
    }
  if (IsInsertEvent (tuple, INITPACKET))
    {
      Prov_rh1_1Eca1Ins (tuple);
    }
  if (IsInsertEvent (tuple, LINKHR))
    {
      Prov_rh1_1Eca2Ins (tuple);
    }
  if (IsRecvEvent (tuple, PACKET))
    {
      Prov_rh2_1_eca (tuple);
    }
  if (IsRecvEvent (tuple, ERECVPACKETTEMP))
    {
      Prov_rh2_2_eca (tuple);
    }
  if (IsRecvEvent (tuple, ERECVPACKETTEMP))
    {
      Prov_rh2_3_eca (tuple);
    }
  if (IsRecvEvent (tuple, ERECVPACKET))
    {
      Prov_rh2_4_eca (tuple);
    }
  if (IsRecvEvent (tuple, ERECVPACKET))
    {
      Prov_rh2_5_eca (tuple);
    }
}

void
PktfwdNormProv::Prov_rs1_1_eca (Ptr<Tuple> packet)
{
  RAPIDNET_LOG_INFO ("Prov_rs1_1_eca triggered");

  Ptr<RelationBase> result;

  result = GetRelation (DEVICE)->Join (
    packet,
    strlist ("device_attr1"),
    strlist ("packet_attr1"));

  result = GetRelation (FLOWENTRY)->Join (
    result,
    strlist ("flowEntry_attr2", "flowEntry_attr1"),
    strlist ("packet_attr3", "packet_attr1"));

  result = GetRelation (LINK)->Join (
    result,
    strlist ("link_attr2", "link_attr1"),
    strlist ("flowEntry_attr3", "packet_attr1"));

  result->Assign (Assignor::New ("PID1",
    FSha1::New (
      Operation::New (RN_PLUS,
        Operation::New (RN_PLUS,
          ValueExpr::New (StrValue::New ("device")),
          VarExpr::New ("packet_attr1")),
        VarExpr::New ("device_attr2")))));

  result->Assign (Assignor::New ("List",
    FAppend::New (
      VarExpr::New ("PID1"))));

  result->Assign (Assignor::New ("PID2",
    FSha1::New (
      Operation::New (RN_PLUS,
        Operation::New (RN_PLUS,
          Operation::New (RN_PLUS,
            Operation::New (RN_PLUS,
              ValueExpr::New (StrValue::New ("packet")),
              VarExpr::New ("packet_attr1")),
            VarExpr::New ("packet_attr2")),
          VarExpr::New ("packet_attr3")),
        VarExpr::New ("packet_attr4")))));

  result->Assign (Assignor::New ("List2",
    FAppend::New (
      VarExpr::New ("PID2"))));

  result->Assign (Assignor::New ("List",
    FConcat::New (
      VarExpr::New ("List"),
      VarExpr::New ("List2"))));

  result->Assign (Assignor::New ("PID3",
    FSha1::New (
      Operation::New (RN_PLUS,
        Operation::New (RN_PLUS,
          Operation::New (RN_PLUS,
            ValueExpr::New (StrValue::New ("flowEntry")),
            VarExpr::New ("packet_attr1")),
          VarExpr::New ("packet_attr3")),
        VarExpr::New ("flowEntry_attr3")))));

  result->Assign (Assignor::New ("List3",
    FAppend::New (
      VarExpr::New ("PID3"))));

  result->Assign (Assignor::New ("List",
    FConcat::New (
      VarExpr::New ("List"),
      VarExpr::New ("List3"))));

  result->Assign (Assignor::New ("PID4",
    FSha1::New (
      Operation::New (RN_PLUS,
        Operation::New (RN_PLUS,
          ValueExpr::New (StrValue::New ("link")),
          VarExpr::New ("packet_attr1")),
        VarExpr::New ("flowEntry_attr3")))));

  result->Assign (Assignor::New ("List4",
    FAppend::New (
      VarExpr::New ("PID4"))));

  result->Assign (Assignor::New ("List",
    FConcat::New (
      VarExpr::New ("List"),
      VarExpr::New ("List4"))));

  result->Assign (Assignor::New ("RLOC",
    VarExpr::New ("packet_attr1")));

  result->Assign (Assignor::New ("R",
    ValueExpr::New (StrValue::New ("rs1"))));

  result->Assign (Assignor::New ("RID",
    FSha1::New (
      Operation::New (RN_PLUS,
        Operation::New (RN_PLUS,
          VarExpr::New ("R"),
          VarExpr::New ("RLOC")),
        VarExpr::New ("List")))));

  result = result->Select (Selector::New (
    Operation::New (RN_EQ,
      VarExpr::New ("device_attr2"),
      ValueExpr::New (Int32Value::New (1)))));

  result = result->Project (
    EPACKETTEMP,
    strlist ("RLOC",
      "flowEntry_attr3",
      "packet_attr2",
      "packet_attr3",
      "packet_attr4",
      "RID",
      "R",
      "List",
      "RLOC"),
    strlist ("epacketTemp_attr1",
      "epacketTemp_attr2",
      "epacketTemp_attr3",
      "epacketTemp_attr4",
      "epacketTemp_attr5",
      "epacketTemp_attr6",
      "epacketTemp_attr7",
      "epacketTemp_attr8",
      RN_DEST));

  Send (result);
}

void
PktfwdNormProv::Prov_rs1_2_eca (Ptr<Tuple> epacketTemp)
{
  RAPIDNET_LOG_INFO ("Prov_rs1_2_eca triggered");

  Ptr<Tuple> result = epacketTemp;

  result = result->Project (
    RULEEXEC,
    strlist ("epacketTemp_attr1",
      "epacketTemp_attr6",
      "epacketTemp_attr7",
      "epacketTemp_attr8"),
    strlist ("ruleExec_attr1",
      "ruleExec_attr2",
      "ruleExec_attr3",
      "ruleExec_attr4"));

  Insert (result);
}

void
PktfwdNormProv::Prov_rs1_3_eca (Ptr<Tuple> epacketTemp)
{
  RAPIDNET_LOG_INFO ("Prov_rs1_3_eca triggered");

  Ptr<Tuple> result = epacketTemp;

  result = result->Project (
    EPACKET,
    strlist ("epacketTemp_attr2",
      "epacketTemp_attr3",
      "epacketTemp_attr4",
      "epacketTemp_attr5",
      "epacketTemp_attr6",
      "epacketTemp_attr1",
      "epacketTemp_attr2"),
    strlist ("epacket_attr1",
      "epacket_attr2",
      "epacket_attr3",
      "epacket_attr4",
      "epacket_attr5",
      "epacket_attr6",
      RN_DEST));

  Send (result);
}

void
PktfwdNormProv::Prov_rs1_4_eca (Ptr<Tuple> epacket)
{
  RAPIDNET_LOG_INFO ("Prov_rs1_4_eca triggered");

  Ptr<Tuple> result = epacket;

  result = result->Project (
    PACKET,
    strlist ("epacket_attr1",
      "epacket_attr2",
      "epacket_attr3",
      "epacket_attr4"),
    strlist ("packet_attr1",
      "packet_attr2",
      "packet_attr3",
      "packet_attr4"));

  SendLocal (result);
}

void
PktfwdNormProv::Prov_rs1_5_eca (Ptr<Tuple> epacket)
{
  RAPIDNET_LOG_INFO ("Prov_rs1_5_eca triggered");

  Ptr<Tuple> result = epacket;

  result->Assign (Assignor::New ("VID",
    FSha1::New (
      Operation::New (RN_PLUS,
        Operation::New (RN_PLUS,
          Operation::New (RN_PLUS,
            Operation::New (RN_PLUS,
              ValueExpr::New (StrValue::New ("packet")),
              VarExpr::New ("epacket_attr1")),
            VarExpr::New ("epacket_attr2")),
          VarExpr::New ("epacket_attr3")),
        VarExpr::New ("epacket_attr4")))));

  result = result->Project (
    PROV,
    strlist ("epacket_attr1",
      "VID",
      "epacket_attr5",
      "epacket_attr6"),
    strlist ("prov_attr1",
      "prov_attr2",
      "prov_attr3",
      "prov_attr4"));

  SendLocal (result);
}

void
PktfwdNormProv::Prov_rh1_1Eca0Ins (Ptr<Tuple> device)
{
  RAPIDNET_LOG_INFO ("Prov_rh1_1Eca0Ins triggered");

  Ptr<RelationBase> result;

  result = GetRelation (INITPACKET)->Join (
    device,
    strlist ("initPacket_attr1"),
    strlist ("device_attr1"));

  result = GetRelation (LINKHR)->Join (
    result,
    strlist ("linkhr_attr1"),
    strlist ("device_attr1"));

  result->Assign (Assignor::New ("PID1",
    FSha1::New (
      Operation::New (RN_PLUS,
        Operation::New (RN_PLUS,
          ValueExpr::New (StrValue::New ("device")),
          VarExpr::New ("device_attr1")),
        VarExpr::New ("device_attr2")))));

  result->Assign (Assignor::New ("List",
    FAppend::New (
      VarExpr::New ("PID1"))));

  result->Assign (Assignor::New ("PID2",
    FSha1::New (
      Operation::New (RN_PLUS,
        Operation::New (RN_PLUS,
          Operation::New (RN_PLUS,
            Operation::New (RN_PLUS,
              ValueExpr::New (StrValue::New ("initPacket")),
              VarExpr::New ("device_attr1")),
            VarExpr::New ("initPacket_attr2")),
          VarExpr::New ("initPacket_attr3")),
        VarExpr::New ("initPacket_attr4")))));

  result->Assign (Assignor::New ("List2",
    FAppend::New (
      VarExpr::New ("PID2"))));

  result->Assign (Assignor::New ("List",
    FConcat::New (
      VarExpr::New ("List"),
      VarExpr::New ("List2"))));

  result->Assign (Assignor::New ("PID3",
    FSha1::New (
      Operation::New (RN_PLUS,
        Operation::New (RN_PLUS,
          ValueExpr::New (StrValue::New ("linkhr")),
          VarExpr::New ("device_attr1")),
        VarExpr::New ("linkhr_attr2")))));

  result->Assign (Assignor::New ("List3",
    FAppend::New (
      VarExpr::New ("PID3"))));

  result->Assign (Assignor::New ("List",
    FConcat::New (
      VarExpr::New ("List"),
      VarExpr::New ("List3"))));

  result->Assign (Assignor::New ("RLOC",
    VarExpr::New ("device_attr1")));

  result->Assign (Assignor::New ("R",
    ValueExpr::New (StrValue::New ("rh1"))));

  result->Assign (Assignor::New ("RID",
    FSha1::New (
      Operation::New (RN_PLUS,
        Operation::New (RN_PLUS,
          VarExpr::New ("R"),
          VarExpr::New ("RLOC")),
        VarExpr::New ("List")))));

  result = result->Select (Selector::New (
    Operation::New (RN_EQ,
      VarExpr::New ("device_attr2"),
      ValueExpr::New (Int32Value::New (1)))));

  result = result->Project (
    EPACKETTEMP,
    strlist ("RLOC",
      "linkhr_attr2",
      "initPacket_attr2",
      "initPacket_attr3",
      "initPacket_attr4",
      "RID",
      "R",
      "List",
      "RLOC"),
    strlist ("epacketTemp_attr1",
      "epacketTemp_attr2",
      "epacketTemp_attr3",
      "epacketTemp_attr4",
      "epacketTemp_attr5",
      "epacketTemp_attr6",
      "epacketTemp_attr7",
      "epacketTemp_attr8",
      RN_DEST));

  Send (result);
}

void
PktfwdNormProv::Prov_rh1_1Eca1Ins (Ptr<Tuple> initPacket)
{
  RAPIDNET_LOG_INFO ("Prov_rh1_1Eca1Ins triggered");

  Ptr<RelationBase> result;

  result = GetRelation (DEVICE)->Join (
    initPacket,
    strlist ("device_attr1"),
    strlist ("initPacket_attr1"));

  result = GetRelation (LINKHR)->Join (
    result,
    strlist ("linkhr_attr1"),
    strlist ("initPacket_attr1"));

  result->Assign (Assignor::New ("PID1",
    FSha1::New (
      Operation::New (RN_PLUS,
        Operation::New (RN_PLUS,
          ValueExpr::New (StrValue::New ("device")),
          VarExpr::New ("initPacket_attr1")),
        VarExpr::New ("device_attr2")))));

  result->Assign (Assignor::New ("List",
    FAppend::New (
      VarExpr::New ("PID1"))));

  result->Assign (Assignor::New ("PID2",
    FSha1::New (
      Operation::New (RN_PLUS,
        Operation::New (RN_PLUS,
          Operation::New (RN_PLUS,
            Operation::New (RN_PLUS,
              ValueExpr::New (StrValue::New ("initPacket")),
              VarExpr::New ("initPacket_attr1")),
            VarExpr::New ("initPacket_attr2")),
          VarExpr::New ("initPacket_attr3")),
        VarExpr::New ("initPacket_attr4")))));

  result->Assign (Assignor::New ("List2",
    FAppend::New (
      VarExpr::New ("PID2"))));

  result->Assign (Assignor::New ("List",
    FConcat::New (
      VarExpr::New ("List"),
      VarExpr::New ("List2"))));

  result->Assign (Assignor::New ("PID3",
    FSha1::New (
      Operation::New (RN_PLUS,
        Operation::New (RN_PLUS,
          ValueExpr::New (StrValue::New ("linkhr")),
          VarExpr::New ("initPacket_attr1")),
        VarExpr::New ("linkhr_attr2")))));

  result->Assign (Assignor::New ("List3",
    FAppend::New (
      VarExpr::New ("PID3"))));

  result->Assign (Assignor::New ("List",
    FConcat::New (
      VarExpr::New ("List"),
      VarExpr::New ("List3"))));

  result->Assign (Assignor::New ("RLOC",
    VarExpr::New ("initPacket_attr1")));

  result->Assign (Assignor::New ("R",
    ValueExpr::New (StrValue::New ("rh1"))));

  result->Assign (Assignor::New ("RID",
    FSha1::New (
      Operation::New (RN_PLUS,
        Operation::New (RN_PLUS,
          VarExpr::New ("R"),
          VarExpr::New ("RLOC")),
        VarExpr::New ("List")))));

  result = result->Select (Selector::New (
    Operation::New (RN_EQ,
      VarExpr::New ("device_attr2"),
      ValueExpr::New (Int32Value::New (1)))));

  result = result->Project (
    EPACKETTEMP,
    strlist ("RLOC",
      "linkhr_attr2",
      "initPacket_attr2",
      "initPacket_attr3",
      "initPacket_attr4",
      "RID",
      "R",
      "List",
      "RLOC"),
    strlist ("epacketTemp_attr1",
      "epacketTemp_attr2",
      "epacketTemp_attr3",
      "epacketTemp_attr4",
      "epacketTemp_attr5",
      "epacketTemp_attr6",
      "epacketTemp_attr7",
      "epacketTemp_attr8",
      RN_DEST));

  Send (result);
}

void
PktfwdNormProv::Prov_rh1_1Eca2Ins (Ptr<Tuple> linkhr)
{
  RAPIDNET_LOG_INFO ("Prov_rh1_1Eca2Ins triggered");

  Ptr<RelationBase> result;

  result = GetRelation (DEVICE)->Join (
    linkhr,
    strlist ("device_attr1"),
    strlist ("linkhr_attr1"));

  result = GetRelation (INITPACKET)->Join (
    result,
    strlist ("initPacket_attr1"),
    strlist ("linkhr_attr1"));

  result->Assign (Assignor::New ("PID1",
    FSha1::New (
      Operation::New (RN_PLUS,
        Operation::New (RN_PLUS,
          ValueExpr::New (StrValue::New ("device")),
          VarExpr::New ("linkhr_attr1")),
        VarExpr::New ("device_attr2")))));

  result->Assign (Assignor::New ("List",
    FAppend::New (
      VarExpr::New ("PID1"))));

  result->Assign (Assignor::New ("PID2",
    FSha1::New (
      Operation::New (RN_PLUS,
        Operation::New (RN_PLUS,
          Operation::New (RN_PLUS,
            Operation::New (RN_PLUS,
              ValueExpr::New (StrValue::New ("initPacket")),
              VarExpr::New ("linkhr_attr1")),
            VarExpr::New ("initPacket_attr2")),
          VarExpr::New ("initPacket_attr3")),
        VarExpr::New ("initPacket_attr4")))));

  result->Assign (Assignor::New ("List2",
    FAppend::New (
      VarExpr::New ("PID2"))));

  result->Assign (Assignor::New ("List",
    FConcat::New (
      VarExpr::New ("List"),
      VarExpr::New ("List2"))));

  result->Assign (Assignor::New ("PID3",
    FSha1::New (
      Operation::New (RN_PLUS,
        Operation::New (RN_PLUS,
          ValueExpr::New (StrValue::New ("linkhr")),
          VarExpr::New ("linkhr_attr1")),
        VarExpr::New ("linkhr_attr2")))));

  result->Assign (Assignor::New ("List3",
    FAppend::New (
      VarExpr::New ("PID3"))));

  result->Assign (Assignor::New ("List",
    FConcat::New (
      VarExpr::New ("List"),
      VarExpr::New ("List3"))));

  result->Assign (Assignor::New ("RLOC",
    VarExpr::New ("linkhr_attr1")));

  result->Assign (Assignor::New ("R",
    ValueExpr::New (StrValue::New ("rh1"))));

  result->Assign (Assignor::New ("RID",
    FSha1::New (
      Operation::New (RN_PLUS,
        Operation::New (RN_PLUS,
          VarExpr::New ("R"),
          VarExpr::New ("RLOC")),
        VarExpr::New ("List")))));

  result = result->Select (Selector::New (
    Operation::New (RN_EQ,
      VarExpr::New ("device_attr2"),
      ValueExpr::New (Int32Value::New (1)))));

  result = result->Project (
    EPACKETTEMP,
    strlist ("RLOC",
      "linkhr_attr2",
      "initPacket_attr2",
      "initPacket_attr3",
      "initPacket_attr4",
      "RID",
      "R",
      "List",
      "RLOC"),
    strlist ("epacketTemp_attr1",
      "epacketTemp_attr2",
      "epacketTemp_attr3",
      "epacketTemp_attr4",
      "epacketTemp_attr5",
      "epacketTemp_attr6",
      "epacketTemp_attr7",
      "epacketTemp_attr8",
      RN_DEST));

  Send (result);
}

void
PktfwdNormProv::Prov_rh2_1_eca (Ptr<Tuple> packet)
{
  RAPIDNET_LOG_INFO ("Prov_rh2_1_eca triggered");

  Ptr<RelationBase> result;

  result = GetRelation (DEVICE)->Join (
    packet,
    strlist ("device_attr1"),
    strlist ("packet_attr1"));

  result->Assign (Assignor::New ("PID1",
    FSha1::New (
      Operation::New (RN_PLUS,
        Operation::New (RN_PLUS,
          ValueExpr::New (StrValue::New ("device")),
          VarExpr::New ("packet_attr1")),
        VarExpr::New ("device_attr2")))));

  result->Assign (Assignor::New ("List",
    FAppend::New (
      VarExpr::New ("PID1"))));

  result->Assign (Assignor::New ("PID2",
    FSha1::New (
      Operation::New (RN_PLUS,
        Operation::New (RN_PLUS,
          Operation::New (RN_PLUS,
            Operation::New (RN_PLUS,
              ValueExpr::New (StrValue::New ("packet")),
              VarExpr::New ("packet_attr1")),
            VarExpr::New ("packet_attr2")),
          VarExpr::New ("packet_attr3")),
        VarExpr::New ("packet_attr4")))));

  result->Assign (Assignor::New ("List2",
    FAppend::New (
      VarExpr::New ("PID2"))));

  result->Assign (Assignor::New ("List",
    FConcat::New (
      VarExpr::New ("List"),
      VarExpr::New ("List2"))));

  result->Assign (Assignor::New ("RLOC",
    VarExpr::New ("packet_attr1")));

  result->Assign (Assignor::New ("R",
    ValueExpr::New (StrValue::New ("rh2"))));

  result->Assign (Assignor::New ("RID",
    FSha1::New (
      Operation::New (RN_PLUS,
        Operation::New (RN_PLUS,
          VarExpr::New ("R"),
          VarExpr::New ("RLOC")),
        VarExpr::New ("List")))));

  result = result->Select (Selector::New (
    Operation::New (RN_EQ,
      VarExpr::New ("packet_attr3"),
      VarExpr::New ("packet_attr1"))));

  result = result->Select (Selector::New (
    Operation::New (RN_EQ,
      VarExpr::New ("device_attr2"),
      ValueExpr::New (Int32Value::New (1)))));

  result = result->Project (
    ERECVPACKETTEMP,
    strlist ("RLOC",
      "packet_attr1",
      "packet_attr2",
      "packet_attr3",
      "packet_attr4",
      "RID",
      "R",
      "List",
      "RLOC"),
    strlist ("erecvPacketTemp_attr1",
      "erecvPacketTemp_attr2",
      "erecvPacketTemp_attr3",
      "erecvPacketTemp_attr4",
      "erecvPacketTemp_attr5",
      "erecvPacketTemp_attr6",
      "erecvPacketTemp_attr7",
      "erecvPacketTemp_attr8",
      RN_DEST));

  Send (result);
}

void
PktfwdNormProv::Prov_rh2_2_eca (Ptr<Tuple> erecvPacketTemp)
{
  RAPIDNET_LOG_INFO ("Prov_rh2_2_eca triggered");

  Ptr<Tuple> result = erecvPacketTemp;

  result = result->Project (
    RULEEXEC,
    strlist ("erecvPacketTemp_attr1",
      "erecvPacketTemp_attr6",
      "erecvPacketTemp_attr7",
      "erecvPacketTemp_attr8"),
    strlist ("ruleExec_attr1",
      "ruleExec_attr2",
      "ruleExec_attr3",
      "ruleExec_attr4"));

  Insert (result);
}

void
PktfwdNormProv::Prov_rh2_3_eca (Ptr<Tuple> erecvPacketTemp)
{
  RAPIDNET_LOG_INFO ("Prov_rh2_3_eca triggered");

  Ptr<Tuple> result = erecvPacketTemp;

  result = result->Project (
    ERECVPACKET,
    strlist ("erecvPacketTemp_attr2",
      "erecvPacketTemp_attr3",
      "erecvPacketTemp_attr4",
      "erecvPacketTemp_attr5",
      "erecvPacketTemp_attr6",
      "erecvPacketTemp_attr1",
      "erecvPacketTemp_attr2"),
    strlist ("erecvPacket_attr1",
      "erecvPacket_attr2",
      "erecvPacket_attr3",
      "erecvPacket_attr4",
      "erecvPacket_attr5",
      "erecvPacket_attr6",
      RN_DEST));

  Send (result);
}

void
PktfwdNormProv::Prov_rh2_4_eca (Ptr<Tuple> erecvPacket)
{
  RAPIDNET_LOG_INFO ("Prov_rh2_4_eca triggered");

  Ptr<Tuple> result = erecvPacket;

  result = result->Project (
    RECVPACKET,
    strlist ("erecvPacket_attr1",
      "erecvPacket_attr2",
      "erecvPacket_attr3",
      "erecvPacket_attr4"),
    strlist ("recvPacket_attr1",
      "recvPacket_attr2",
      "recvPacket_attr3",
      "recvPacket_attr4"));

  Insert (result);
}

void
PktfwdNormProv::Prov_rh2_5_eca (Ptr<Tuple> erecvPacket)
{
  RAPIDNET_LOG_INFO ("Prov_rh2_5_eca triggered");

  Ptr<Tuple> result = erecvPacket;

  result->Assign (Assignor::New ("VID",
    FSha1::New (
      Operation::New (RN_PLUS,
        Operation::New (RN_PLUS,
          Operation::New (RN_PLUS,
            Operation::New (RN_PLUS,
              ValueExpr::New (StrValue::New ("recvPacket")),
              VarExpr::New ("erecvPacket_attr1")),
            VarExpr::New ("erecvPacket_attr2")),
          VarExpr::New ("erecvPacket_attr3")),
        VarExpr::New ("erecvPacket_attr4")))));

  result = result->Project (
    PROV,
    strlist ("erecvPacket_attr1",
      "VID",
      "erecvPacket_attr5",
      "erecvPacket_attr6"),
    strlist ("prov_attr1",
      "prov_attr2",
      "prov_attr3",
      "prov_attr4"));

  SendLocal (result);
}


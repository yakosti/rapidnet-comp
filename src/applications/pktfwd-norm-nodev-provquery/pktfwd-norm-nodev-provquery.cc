/* A RapidNet application. Generated by RapidNet compiler. */

#include "pktfwd-norm-nodev-provquery.h"
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
using namespace ns3::rapidnet::pktfwdnormnodevprovquery;

const string PktfwdNormNodevProvquery::PRETURN = "pReturn";
const string PktfwdNormNodevProvquery::PROVQUERY = "provQuery";
const string PktfwdNormNodevProvquery::RECORDS = "records";
const string PktfwdNormNodevProvquery::TUPLE = "tuple";

NS_LOG_COMPONENT_DEFINE ("PktfwdNormNodevProvquery");
NS_OBJECT_ENSURE_REGISTERED (PktfwdNormNodevProvquery);

TypeId
PktfwdNormNodevProvquery::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::rapidnet::pktfwdnormnodevprovquery::PktfwdNormNodevProvquery")
    .SetParent<RapidNetApplicationBase> ()
    .AddConstructor<PktfwdNormNodevProvquery> ()
    ;
  return tid;
}

PktfwdNormNodevProvquery::PktfwdNormNodevProvquery()
{
  NS_LOG_FUNCTION_NOARGS ();
}

PktfwdNormNodevProvquery::~PktfwdNormNodevProvquery()
{
  NS_LOG_FUNCTION_NOARGS ();
}

void
PktfwdNormNodevProvquery::DoDispose (void)
{
  NS_LOG_FUNCTION_NOARGS ();

  RapidNetApplicationBase::DoDispose ();
}

void
PktfwdNormNodevProvquery::StartApplication (void)
{
  NS_LOG_FUNCTION_NOARGS ();

  RapidNetApplicationBase::StartApplication ();
  RAPIDNET_LOG_INFO("PktfwdNormNodevProvquery Application Started");
}

void
PktfwdNormNodevProvquery::StopApplication ()
{
  NS_LOG_FUNCTION_NOARGS ();

  RapidNetApplicationBase::StopApplication ();
  RAPIDNET_LOG_INFO("PktfwdNormNodevProvquery Application Stopped");
}

void
PktfwdNormNodevProvquery::InitDatabase ()
{
  //RapidNetApplicationBase::InitDatabase ();

  AddRelationWithKeys (RECORDS, attrdeflist (
    attrdef ("records_attr1", IPV4),
    attrdef ("records_attr2", ID),
    attrdef ("records_attr3", ID)));

  AddRelationWithKeys (TUPLE, attrdeflist (
    attrdef ("tuple_attr1", IPV4),
    attrdef ("tuple_attr2", STR)));

}

void
PktfwdNormNodevProvquery::DemuxRecv (Ptr<Tuple> tuple)
{
  RapidNetApplicationBase::DemuxRecv (tuple);

  if (IsInsertEvent (tuple, TUPLE))
    {
      Rq1Eca0Ins (tuple);
    }
  if (IsRecvEvent (tuple, PRETURN))
    {
      Rq2_eca (tuple);
    }
}

void
PktfwdNormNodevProvquery::Rq1Eca0Ins (Ptr<Tuple> tuple)
{
  RAPIDNET_LOG_INFO ("Rq1Eca0Ins triggered");

  Ptr<Tuple> result = tuple;

  result->Assign (Assignor::New ("VID",
    FSha1::New (
      Operation::New (RN_PLUS,
        Operation::New (RN_PLUS,
          Operation::New (RN_PLUS,
            Operation::New (RN_PLUS,
              VarExpr::New ("tuple_attr2"),
              VarExpr::New ("tuple_attr3")),
            VarExpr::New ("tuple_attr4")),
          VarExpr::New ("tuple_attr5")),
        VarExpr::New ("tuple_attr6")))));

  result->Assign (Assignor::New ("Time",
    FNow::New (
)));

  result->Assign (Assignor::New ("QID",
    FSha1::New (
      Operation::New (RN_PLUS,
        Operation::New (RN_PLUS,
          ValueExpr::New (StrValue::New ("")),
          VarExpr::New ("VID")),
        VarExpr::New ("Time")))));

  result = result->Project (
    PROVQUERY,
    strlist ("tuple_attr3",
      "QID",
      "VID",
      "tuple_attr1",
      "tuple_attr3"),
    strlist ("provQuery_attr1",
      "provQuery_attr2",
      "provQuery_attr3",
      "provQuery_attr4",
      RN_DEST));

  Send (result);
}

void
PktfwdNormNodevProvquery::Rq2_eca (Ptr<Tuple> pReturn)
{
  RAPIDNET_LOG_INFO ("Rq2_eca triggered");

  Ptr<Tuple> result = pReturn;

  result = result->Project (
    RECORDS,
    strlist ("pReturn_attr1",
      "pReturn_attr2",
      "pReturn_attr3",
      "pReturn_attr4"),
    strlist ("records_attr1",
      "records_attr2",
      "records_attr3",
      "records_attr4"));

  Insert (result);
}

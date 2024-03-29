/* A RapidNet application. Generated by RapidNet compiler. */

#ifndef PKTFWDNORMPROVPROVQUERYOCT0116_H
#define PKTFWDNORMPROVPROVQUERYOCT0116_H

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
namespace pktfwdnormprovprovqueryoct0116 {

class PktfwdNormProvProvqueryOct0116 : public RapidNetApplicationBase
{
public:
  static const string PRETURN;
  static const string PROVQUERY;
  static const string RECORDS;
  static const string TUPLE;

  static TypeId GetTypeId (void);

  PktfwdNormProvProvqueryOct0116 ();

  virtual ~PktfwdNormProvProvqueryOct0116 ();

protected:

  virtual void DoDispose (void);

  virtual void StartApplication (void);

  virtual void StopApplication (void);

  virtual void InitDatabase (void);

  virtual void DemuxRecv (Ptr<Tuple> tuple);

  virtual void Rq1Eca0Ins (Ptr<Tuple> tuple);

  virtual void Rq2_eca (Ptr<Tuple> pReturn);

};

} // namespace pktfwdnormprovprovqueryoct0116
} // namespace rapidnet
} // namespace ns3

#endif // PKTFWDNORMPROVPROVQUERYOCT0116_H

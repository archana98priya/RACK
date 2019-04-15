#include "tcp-tlp.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("TcpTlp");
NS_OBJECT_ENSURE_REGISTERED (TcpTlp);

TypeId
TcpTlp::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::TcpTlp")
    .SetParent<Object> ()
    .AddConstructor<TcpTlp> ()
    .SetGroupName ("Internet")
  ;
  return tid;
}

TcpTlp::TcpTlp (void)
   : Object (),
    m_srtt (0),
    m_alpha (0.125),
    m_pto(MilliSeconds(2)),
    m_tlpRtt (0)
{
  NS_LOG_FUNCTION (this);
}

TcpTlp::TcpTlp (const TcpTlp &other)
  : Object (other),
    m_srtt (other.m_srtt),
    m_alpha (other.m_alpha),
    m_pto(other.m_pto),
    m_tlpRtt (other.m_tlpRtt)

{
  NS_LOG_FUNCTION (this);
}

TcpTlp::~TcpTlp ()
{
  NS_LOG_FUNCTION (this);
}

// Calculate the value of PTO
void 
TcpTlp::CalculatePto(Time lastRtt, uint32_t flightsize, Time rto, Time curr_pto)
{
  NS_LOG_FUNCTION (this);
    Time rtt = lastRtt;
    if (rtt > Seconds(0))
    {
        m_tlpRtt = rtt;
    }
    // Compute SRTT - Smooth round trip time
    if (m_srtt == 0)
    {
      m_srtt = m_tlpRtt.GetMilliSeconds ();
    }
    else
    {
      m_srtt = (1 - m_alpha) * m_srtt + m_alpha * m_tlpRtt.GetMilliSeconds ();
    }
    // Update PTO
    if (m_srtt != -1)
    {
        curr_pto = MilliSeconds(2 * m_srtt);
        if (flightsize == 1)
        {
          // To compensate for a potential long delayed ACK timer at the receiver
          curr_pto += MilliSeconds(200) ;
        }
        else
        {
          curr_pto += MilliSeconds(2);
        }
    }      
    else
    {
        curr_pto = Seconds(1.0);
    }
    // The max value for PTO should be RTO
    curr_pto = std :: min (rto , curr_pto) ; 
    m_pto = curr_pto;   
}
}

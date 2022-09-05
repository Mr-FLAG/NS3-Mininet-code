/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2019 NITK Surathkal
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Apoorva Bhargava <apoorvabhargava13@gmail.com>
 *         Mohit P. Tahiliani <tahiliani@nitk.edu.in>
 *
 */

#include "tcp-fixed.h"
#include "ns3/log.h"
#include "ns3/simulator.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("TcpFixed");
NS_OBJECT_ENSURE_REGISTERED (TcpFixed);

TypeId
TcpFixed::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::TcpFixed")
    .SetParent<TcpCongestionOps> ()
    .SetGroupName ("Internet")
    .AddConstructor<TcpFixed> ()
  ;
  return tid;
}

TcpFixed::TcpFixed (void) : TcpCongestionOps ()
{
  NS_LOG_FUNCTION (this);
}

TcpFixed::TcpFixed (const TcpFixed& sock)
  : TcpCongestionOps (sock)
{
  NS_LOG_FUNCTION (this);
}

TcpFixed::~TcpFixed (void)
{
}

uint32_t
TcpFixed::SlowStart (Ptr<TcpSocketState> tcb, uint32_t segmentsAcked)
{
  NS_LOG_FUNCTION (this << tcb << segmentsAcked);

  //tcb->m_cWnd = 5000;
  
  if (segmentsAcked >= 1)
    {
      //tcp->m_cWnd = 5000;
      
      uint32_t sndCwnd = tcb->m_cWnd;
      tcb->m_cWnd = std::min ((sndCwnd + (segmentsAcked * tcb->m_segmentSize)), (uint32_t)tcb->m_ssThresh);
      NS_LOG_INFO ("In SlowStart, updated to cwnd " << tcb->m_cWnd << " ssthresh " << tcb->m_ssThresh);
      return segmentsAcked - ((tcb->m_cWnd - sndCwnd) / tcb->m_segmentSize);
      
    }
  
  return 0;
}

void
TcpFixed::CongestionAvoidance (Ptr<TcpSocketState> tcb, uint32_t segmentsAcked)
{
  NS_LOG_FUNCTION (this << tcb << segmentsAcked);
  //tcb->m_cWnd = 5000;
  
  uint32_t w = tcb->m_cWnd / tcb->m_segmentSize;
  NS_LOG_DEBUG ("w in segments " << w << " m_cWndCnt " << m_cWndCnt << " segments acked " << segmentsAcked);
  if (m_cWndCnt >= w)
    {
      m_cWndCnt = 0;
      tcb->m_cWnd += tcb->m_segmentSize;
      NS_LOG_DEBUG ("Adding 1 segment to m_cWnd");
    }

  m_cWndCnt += segmentsAcked;
  NS_LOG_DEBUG ("Adding 1 segment to m_cWndCnt");
  if (m_cWndCnt >= w)
    {
      uint32_t delta = m_cWndCnt / w;

      m_cWndCnt -= delta * w;
      tcb->m_cWnd += delta * tcb->m_segmentSize;
      NS_LOG_DEBUG ("Subtracting delta * w from m_cWndCnt " << delta * w);
    }
  NS_LOG_DEBUG ("At end of CongestionAvoidance(), m_cWnd: " << tcb->m_cWnd << " m_cWndCnt: " << m_cWndCnt);
  
}

void
TcpFixed::IncreaseWindow (Ptr<TcpSocketState> tcb, uint32_t segmentsAcked)
{
  NS_LOG_FUNCTION (this << tcb << segmentsAcked);
    //bool temp = true;
    //uint32_t thresh_hold = 5000;
    
    
    //std::cout << "tcb->m_rcvTimestampValue: "<< tcb->m_rcvTimestampValue << std::endl;
    
    if (tcb->m_rcvTimestampValue % 360 == 0){
      tcb->m_cWnd *= 1.1;
      //std::cout << tcb->m_rcvTimestampValue << std::endl;
    }
    /*
    if (tcb->m_cWnd < thresh_hold)
        tcb->m_cWnd = 5000;
    else {
        if (temp){
            tcb->m_cWnd -= 1;
            temp = false;
        }
        else{
            tcb->m_cWnd += 1;
            temp = true;
        } 
    }*/
    
  /*
  // Linux tcp_in_slow_start() condition
  if (tcb->m_cWnd < tcb->m_ssThresh)
    {
      NS_LOG_DEBUG ("In slow start, m_cWnd " << tcb->m_cWnd << " m_ssThresh " << tcb->m_ssThresh);
      segmentsAcked = SlowStart (tcb, segmentsAcked);
    }
  else//Congestion avoidance condition
    {
      NS_LOG_DEBUG ("In cong. avoidance, m_cWnd " << tcb->m_cWnd << " m_ssThresh " << tcb->m_ssThresh);
      CongestionAvoidance (tcb, segmentsAcked);
    }
  */
}

std::string
TcpFixed::GetName () const
{
  return "TcpFixed";
}

uint32_t
TcpFixed::GetSsThresh (Ptr<const TcpSocketState> state,
                           uint32_t bytesInFlight)
{
  NS_LOG_FUNCTION (this << state << bytesInFlight);

  // In Linux, it is written as:  return max(tp->snd_cwnd >> 1U, 2U);
  return std::max<uint32_t> (2 * state->m_segmentSize, state->m_cWnd / 2);
}

Ptr<TcpCongestionOps>
TcpFixed::Fork ()
{
  return CopyObject<TcpFixed> (this);
}

} // namespace ns3
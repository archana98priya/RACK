/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2018 NITK Surathkal
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
 * Author: Shikha Bakshi <shikhabakshi912@gmail.com>
 *         Mohit P. Tahiliani <tahiliani@nitk.edu.in>
 *
 */
#pragma once

#include "ns3/object.h"
#include "ns3/traced-value.h"
#include "ns3/sequence-number.h"
#include "ns3/nstime.h"
#include "ns3/tcp-option-sack.h"
#include "ns3/packet.h"
#include "ns3/tcp-socket-state.h"
#include "ns3/simulator.h"

namespace ns3 {

class TcpTlp : public Object
{
public:
  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);

  /**
   * \brief Constructor
   */
  TcpTlp ();

  /**
   * \brief Copy constructor.
   * \param other object to copy.
   */
  TcpTlp (const TcpTlp &other);

  /**
   * \brief Deconstructor
   */
  virtual ~TcpTlp ();

 

 void CalculatePto(Time srtt, uint32_t flightsize, Time rto, Time curr_pto);

 



 

  /**
   * \brief updates RACK parameters
   * 
   * \ param tcp tcp header of the received ACK
   * \ param retrans whether the packet is retransmitted or not
   * \ param xmitTs transmission timestamp of the packet
   * \ param endSeq end sequence number of packet
   * \ param sndNxt SND.NXT when the RTT is updated
  
  virtual void UpdateStats (uint32_t tser, bool retrans, Time xmitTs, SequenceNumber32 endSseq,
                            SequenceNumber32 sndNxt, Time lastRtt);
  */



private:
  Time             m_rackXmitTs                {0}; //!< Latest transmission timestamp of Rack.packet
  SequenceNumber32 m_rackEndSeq                {0}; //!< Ending sequence number of Rack.packet
  Time             m_rackRtt                   {0}; //!< RTT of the most recently transmitted packet that has been acknowledged
  double           m_reoWnd                    {0}; //!< Re-ordering Window
  Time             m_minRtt                    {0}; //!< Minimum RTT
  SequenceNumber32 m_rttSeq                    {0}; //!< SND.NXT when RACK.rtt is updated
  bool             m_dsack                 {false}; //!< If a DSACK option has been received since last RACK.reo_wnd change
  uint32_t         m_reoWndIncr                {1}; //!< Multiplier applied to adjust RACK.reo_wnd
  uint32_t         m_reoWndPersist            {16}; //!< Number of loss recoveries before resetting RACK.reo_wnd 
  double           m_srtt                      {0}; //!< Smoothened RTT (SRTT) as specified in [RFC6298]
  double           m_alpha                 {0.125}; //!< EWMA constant for calculation of SRTT (alpha = 1/8)
  
public:
  Time             m_pto                       {0}; //!< PTO values>  
  Time             m_tlpRtt                    {0}; //!< RTT value used for TLP>
};
} // namespace ns3

/* TCP_RACK_H */

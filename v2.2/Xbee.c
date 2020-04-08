/*
 * Copyright (c) 2019 Digi International Inc.,
 * All rights not expressly granted are reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Digi International Inc., 9350 Excelsior Blvd., Suite 700, Hopkins, MN 55343
 * ===========================================================================
 */

/**
    @addtogroup xbee_firmware
    @{
    @file xbee_bl_gen3.c
    Support code for bootloader used on "Gen3" products (including S3B, S6,
    S6B, XLR, Cellular, SX, SX868, S8).  Firmware updates use .ebin files.
    For Cellular products, all XBee Cellular modules (Cat 1 Verizon and 3G
    Global) use this bootloader.  XBee3 Cellular modules (Cat 1 AT&T and
    LTE-M/NB-IoT) with firmware versions (ATVR values) ending in 0C or lower
    do as well.
    After installing firmware *0F (1140F or 3100F) on an XBee3 Cellular module,
    it will update the hardware to use the "Gecko bootloader" and .gbl files
    for further firmware updates.  See xbee/firmware.h and xbee_firmware.c
    for .gbl and Gecko bootloader support.
    Define XBEE_BL_GEN3_VERBOSE for debugging messages.
*/


#include <stdlib.h>
#include "xbee.h"

//volatile static int xbee_rx_state=eXbeeStraightSerialRxInit;
volatile static int xbee_rx_is_error=0;
volatile static unsigned long xbee_rx_state_byte_num=0;
struct  xbee_rx_packet;
static void (*_debugCallback)(void)=0;
static void (*_debug)(const char* debugMsg)=0;
//static long xbee_rx_exp_payload_len=0;
//volatile static struct XBEE_RX_PACKET xbee_rx_packet;

void checkcal()
{
uint16_t checksum;

}

/*
//void initXbeeModule(void (*debugCallback)(void),
//		    void (*debug)(const char*) )
//{
//  _debugCallback=debugCallback;
//  _debug=debug;
//}

//static void debugCallback(void)
//{
//  if(0 != _debugCallback)
//    (*_debugCallback)();
//}
*/
/*
static void initXbeeMsgStart(char c)
{
  xbee_rx_state=eXbeeStraightSerialRxStartMsg;
  xbee_rx_state_byte_num=0;
  xbee_rx_is_error=0;
//   if('<' ==c || '{' ==c) 
  if('{' ==c)
    xbee_rx_packet.swarm_msg_type=eLinkArt;
//   else  
//    xbee_rx_packet.swarm_msg_type=eLinkMotorControl; 
  xbee_rx_packet.swarm_msg_payload[xbee_rx_state_byte_num]=c;
}
*/
/*
void handleXbeeSerial(char c, int isError)
{
  debugCallback();
  debug("\r\nin handleXbeeSerial");
  //if it's an error flag and discard till the start of the next message
  if(isError){
    //debugCallback();
    debug("\nerror flag set");
    xbee_rx_is_error=isError;
    return;
  }
  switch(xbee_rx_state){
  case eXbeeStraightSerialRxInit:
 //     if('$'==c || '<'== c || '{' ==c){ 
    if('{' ==c){
      //debugCallback();
      initXbeeMsgStart(c);
    }
    break;
  case eXbeeStraightSerialRxStartMsg:
//     if('$' ==c || '<'==c || '{'==c){ 
    if('{'==c){
      //empty message
      initXbeeMsgStart(c);
    }
    else{
      xbee_rx_state=eXbeeStraightSerialRxPayload;
      xbee_rx_state_byte_num++;
      xbee_rx_packet.swarm_msg_payload[xbee_rx_state_byte_num]=c;
    }
    break;
  case eXbeeStraightSerialRxPayload:
    if('{'==c){
      //empty message
      initXbeeMsgStart(c);
    }
//     else if('$'==c|| '>'==c || '}'==c) 
//        { 
// 	 if('>'==c || '}'==c) 
// 	   xbee_rx_packet.swarm_msg_payload[++xbee_rx_state_byte_num]=c; 

// 	 //if not error first dispatch old message 
// 	 if(!xbee_rx_is_error){ 
// 	   xbee_rx_packet.swarm_msg_length[0] =  
// 	     (char)(xbee_rx_state_byte_num>>8); 
// 	   xbee_rx_packet.swarm_msg_length[1] = (char)xbee_rx_state_byte_num; 
//	   xbee_rx_packet.swarm_msg_payload[xbee_rx_state_byte_num+1]=';'; 
// 	   xbee_rx_packet.swarm_msg_payload[xbee_rx_state_byte_num+2]='\0'; 
// 	   pushQ(xbee_rx_packet); 
// 	 } 
// 	 initXbeeMsgStart(c); 
//        } 
    else if('}'==c)
       {
	 xbee_rx_packet.swarm_msg_payload[++xbee_rx_state_byte_num]=c;

	 //if not error first dispatch old message
	 if(!xbee_rx_is_error){
	   xbee_rx_packet.swarm_msg_length[0] = 
	     (char)(xbee_rx_state_byte_num>>8);
	   xbee_rx_packet.swarm_msg_length[1] = (char)xbee_rx_state_byte_num;
// 	   xbee_rx_packet.swarm_msg_payload[xbee_rx_state_byte_num+1]=';'; 
	   xbee_rx_packet.swarm_msg_payload[xbee_rx_state_byte_num+1]='\0';
	   pushQ(xbee_rx_packet);
	 }
	 //initXbeeMsgStart(c);
	 xbee_rx_state=eXbeeStraightSerialRxInit;
       }
     else
       {
	 //check for max size
	 xbee_rx_state_byte_num++;
	 if(xbee_rx_state_byte_num 
	    <= (MAX_SWARM_MSG_LENGTH-1)/*leave 1 byte for the new line )*/ 
/*	   xbee_rx_packet.swarm_msg_payload[xbee_rx_state_byte_num]=c;
	 //else ignore till the end
       }
     break;
     //default:
    //debugCallback();
  }
  //debugCallback();
}
*/

/*
void handleXbeeSerialBuf(const char* buf, long nNumBytes)
{
  for(int i=0; i < nNumBytes; i++)
    {
      handleXbeeSerial(buf[i], 0);
    }
}

static void initRxBuffers(void)
{
  xbee_rx_state=eRxStateStart;
  xbee_rx_state_byte_num=0;
  xbee_rx_exp_payload_len=0;
}

void handleXBeeSerialRx(char c, int isError)
{
  switch(c){
  case eRxStateStart : 
    if(XBEE_FRAME_ID == c)
      xbee_rx_state = eRxStateLength;
    //else there is nothing for me to do. just wait for frame start
    break;
  case eRxStateLength :
    if(xbee_rx_state_byte_num < 2)
      {
	xbee_rx_packet.packet_length[xbee_rx_state_byte_num++]=c;
	break;
      }
    else if(2 == xbee_rx_state_byte_num)
      {
	//init and fall through
	xbee_rx_state_byte_num=0;
	xbee_rx_state=eRxStateAPIId;
      }
  case eRxStateAPIId :
    if(0 == xbee_rx_state_byte_num)
      {
	xbee_rx_packet.api_identifier=c;
	xbee_rx_state_byte_num++;
	break;
      }
    else
      {
	//init and fall through
	xbee_rx_state_byte_num=0;
	xbee_rx_state=eRxStateSrcAddr;
      }
  case eRxStateSrcAddr:
    if(xbee_rx_state_byte_num < 2)
      {
	xbee_rx_packet.source_address[xbee_rx_state_byte_num++] = c;
	break;
      }
    else
      {
	//change state, init and fall thru
	xbee_rx_state=eRxStateRssi;
	xbee_rx_state_byte_num=0;
      }
  case eRxStateRssi:
    if(0 ==  xbee_rx_state_byte_num)
      {
	xbee_rx_packet.rssi_indicator=c;
	xbee_rx_state_byte_num++;
	break;
      }
    else
      {
	//change state, init and fall thru
	xbee_rx_state=eRxStateBroadcastOpt;
	xbee_rx_state_byte_num=0;
      }
  case eRxStateBroadcastOpt:
    if(0 == xbee_rx_state_byte_num)
      {
	xbee_rx_state_byte_num++;
	break;
      }
    else
      {
	xbee_rx_exp_payload_len = atol((char*)xbee_rx_packet.packet_length);
	//account for the bytes we have already read
	xbee_rx_exp_payload_len = xbee_rx_exp_payload_len -5;
	//change state, init and fall thru
	xbee_rx_state=eRxStatePayload;
	xbee_rx_state_byte_num=0;
      }
  case eRxStatePayload:
    if(xbee_rx_state_byte_num< xbee_rx_exp_payload_len)
      {
	xbee_rx_packet.payload[xbee_rx_state_byte_num++] = c;
	break;
      }
    else
      {
	xbee_rx_state_byte_num=0;
	xbee_rx_state=eRxStateChksum;
      }
  case eRxStateChksum:
    xbee_rx_packet.checksum=c;
    //fall through to init
    handleXBeePacket(xbee_rx_packet);
  default:
    //initialise stuff here
    initRxBuffers();
  }
}
*/

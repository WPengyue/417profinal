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


#include <stdint.h>


#define RD_TIMEOUT 10
static char rbuf[254];

#define XBEE_API_FRAME_STARTDELIMITER_TX         0x7E



typedef struct  
{
  char		StartDelimiter;
	uint16_t			wLength;
	char				*frameData;
  char		CheckSum;
} XBEE_API_FRAME ;

typedef struct{
	uint8_t end_sn[8]; //end device serial number
	uint8_t join_stat;
}xbee_dev_t;

void initXbeeModule();
void handleXbeeSerialBuf(const char* , long );
static void initRxBuffers();
void handleXBeeSerialRx(char , int );
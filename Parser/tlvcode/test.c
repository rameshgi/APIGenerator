#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "oampdu.h"
#include "util.h"
#include "information_tlv.h"

extern unsigned char printtLVOAMPDU ( tLVOAMPDU* oampdu );
extern unsigned char unpackOAMPDU ( unsigned char* bitstream, unsigned int streamSize, tLVOAMPDU** unpackedPDU );
extern unsigned char packOAMPDU ( tLVOAMPDU* oampdu, unsigned int* packedPDUSize, unsigned char** packedOAMPDU );
extern unsigned char printHexDump ( unsigned char* bitstream, unsigned int streamSize );

extern unsigned char packINFORMATION_TLV ( tLVINFORMATION_TLV* information_tlv, unsigned int* packedPDUSize, unsigned char** packedINFORMATION_TLV );
extern unsigned char unpackINFORMATION_TLV ( unsigned char* bitstream, unsigned int streamSize, tLVINFORMATION_TLV** unpackedPDU );
extern unsigned char printtLVINFORMATION_TLV ( tLVINFORMATION_TLV* information_tlv );


int main ()
{
  tLVOAMPDU oampdu;
  memset ( &oampdu, '\0', sizeof ( tLVOAMPDU ) );

  unsigned char payload [ 6 ];
  payload [ 0 ] = 0xAA;
  payload [ 1 ] = 0xFF;
  payload [ 2 ] = 0xDD;
  payload [ 3 ] = 0xBB;
  payload [ 4 ] = 0xAA;
  payload [ 5 ] = 0x99;


  oampdu.destination_address [ 0 ] = 0x00;
  oampdu.destination_address [ 1 ] = 0xAA;
  oampdu.destination_address [ 2 ] = 0xBB;
  oampdu.destination_address [ 3 ] = 0xCC;
  oampdu.destination_address [ 4 ] = 0x11;
  oampdu.destination_address [ 5 ] = 0x22;
  oampdu.source_address      [ 0 ] = 0xFF;
  oampdu.source_address      [ 1 ] = 0x33;
  oampdu.source_address      [ 2 ] = 0x99;
  oampdu.source_address      [ 3 ] = 0x00;
  oampdu.source_address      [ 4 ] = 0xAA;
  oampdu.source_address      [ 5 ] = 0xCC;
  oampdu.lengthtype          = 0x8809;
  oampdu.subtype             = 0x03;
  oampdu.flags               = 0x3344;
  oampdu.code                = 0xAA;
  oampdu.payload             = payload;
  oampdu.payload_size        = 6;
  oampdu.fcs                 = 0xAABBFFCC;

  printtLVOAMPDU ( &oampdu );

  unsigned char* packedOAMPDU  = NULL;
  unsigned int   packedPDUSize = 0;
  packOAMPDU     ( &oampdu, &packedPDUSize, &packedOAMPDU );

  printHexDump ( packedOAMPDU, packedPDUSize );

  tLVOAMPDU* unpackedPDU = 0;
  unpackOAMPDU    ( packedOAMPDU, packedPDUSize, &unpackedPDU );
  printtLVOAMPDU ( unpackedPDU );

  free ( packedOAMPDU );
  free ( unpackedPDU );

  

  tLVINFORMATION_TLV infotlv;
  memset ( &infotlv, '\0', sizeof ( infotlv ) );

  unsigned char oui [ 3 ];
  oui [ 0 ] = 0x12;
  oui [ 1 ] = 0x34;
  oui [ 2 ] = 0xFA;

  infotlv.information_type = 0x1A;
  infotlv.information_length = 0xDB;
  infotlv.oam_version = 0x9F;
  infotlv.revision = 0x6C8B;
  infotlv.state = 0xB7;
  infotlv.oam_configuration = 0xFC;
  infotlv.oampdu_configuration = 0x9ABD;
  memcpy ( infotlv.oui, oui, 3 );
  infotlv.vendor_specific_info = 0x4F9DA7C2;

  printtLVINFORMATION_TLV ( &infotlv );
  
  packedPDUSize = 0;
  unsigned char* packedINFORMATION_TLV = 0;
  packINFORMATION_TLV ( &infotlv, &packedPDUSize, &packedINFORMATION_TLV );

  printHexDump ( packedINFORMATION_TLV, packedPDUSize );

  tLVINFORMATION_TLV* newinfotlv = 0;
  unpackINFORMATION_TLV ( packedINFORMATION_TLV, 
                          packedPDUSize, 
			  &newinfotlv );
  printtLVINFORMATION_TLV ( newinfotlv );
  
  free ( packedINFORMATION_TLV );
  free ( newinfotlv );
}

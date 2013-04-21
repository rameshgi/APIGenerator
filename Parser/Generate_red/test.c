#include "oampdu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern unsigned char packOAMPDU ( tlvOAMPDU* oampdu,
                                  unsigned int* packedPduSize,
			          unsigned char** packedOAMPDU );

extern unsigned char unpackOAMPDU ( unsigned char* bitStream,
                                    unsigned int   streamSize,
			            tlvOAMPDU**    unpackedPDU );

extern unsigned char printtlvOAMPDU ( tlvOAMPDU* oampdu );
extern unsigned char printOAMPDU ( unsigned char* bitstream,
                                   unsigned int   streamSize );

int main ()
{
  tlvOAMPDU oampdu;
  memset ( &oampdu, '\0', sizeof ( tlvOAMPDU ) );

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
  oampdu.length_type         = 0x8809;
  oampdu.subtype             = 0x03;
  oampdu.flags               = 0x3344;
  oampdu.code                = 0xAA;
  oampdu.payload             = payload;
  oampdu.payload_size        = 6;
  oampdu.fcs                 = 0xAABBFFCC;

  printtlvOAMPDU ( &oampdu );

  unsigned char* packedOAMPDU  = NULL;
  unsigned int   packedPDUSize = 0;
  packOAMPDU     ( &oampdu, &packedPDUSize, &packedOAMPDU );

  printOAMPDU ( packedOAMPDU, packedPDUSize );

  tlvOAMPDU* unpackedPDU = 0;
  unpackOAMPDU    ( packedOAMPDU, packedPDUSize, &unpackedPDU );
  printtlvOAMPDU ( unpackedPDU );

  free ( packedOAMPDU );
  free ( unpackedPDU );
}

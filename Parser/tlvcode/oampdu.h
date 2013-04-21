// THIS IS A GENERATED FILE

#ifndef __OAMPDU_H__
#define __OAMPDU_H__

typedef struct OAMPDU
{
  unsigned char destination_address [ 6 ];
  unsigned char source_address [ 6 ];
  unsigned short lengthtype;
  unsigned char subtype;
  unsigned short flags;
  unsigned char code;
  unsigned char* payload;
  unsigned int payload_size;
  unsigned int fcs;
} tLVOAMPDU;




// Routine for packing OAMPDU
//    This routine will allocate heap memory for the packed
//    PDU.
//    Client code to deallocate after use 
unsigned char packOAMPDU ( tLVOAMPDU* oampdu, unsigned int* packedPDUSize, unsigned char** packedOAMPDU );

// Routine for Unpacking OAMPDU
//    This routine will allocate heap memory for the packed
//    PDU.
//    Client code to deallocate after use 
unsigned char unpackOAMPDU ( unsigned char* bitstream, unsigned int streamSize, tLVOAMPDU** unpackedPDU );

//Debug Routines
unsigned char printtLVOAMPDU ( tLVOAMPDU* oampdu );





 #endif


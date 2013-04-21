// THIS IS A GENERATED FILE

#ifndef __WIMAX_MAC_FRAME_H__
#define __WIMAX_MAC_FRAME_H__

typedef struct WIMAX_MAC_FRAME
{
  unsigned char ht;
  unsigned char ec;
  unsigned char type [ 6 ];
  unsigned char esf;
  unsigned char ci;
  unsigned char eks;
  unsigned char len [ 11 ];
  unsigned char cid [ 16 ];
  unsigned long long hcs;
} tLVWIMAX_MAC_FRAME;




// Routine for packing OAMPDU
//    This routine will allocate heap memory for the packed
//    PDU.
//    Client code to deallocate after use 
unsigned char packWIMAX_MAC_FRAME ( tLVWIMAX_MAC_FRAME* wimax_mac_frame, unsigned int* packedPDUSize, unsigned char** packedWIMAX_MAC_FRAME );

// Routine for Unpacking OAMPDU
//    This routine will allocate heap memory for the packed
//    PDU.
//    Client code to deallocate after use 
unsigned char unpackWIMAX_MAC_FRAME ( unsigned char* bitstream, unsigned int streamSize, tLVWIMAX_MAC_FRAME** unpackedPDU );

//Debug Routines
unsigned char printtLVWIMAX_MAC_FRAME ( tLVWIMAX_MAC_FRAME* wimax_mac_frame );





 #endif


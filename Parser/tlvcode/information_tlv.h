// THIS IS A GENERATED FILE

#ifndef __INFORMATION_TLV_H__
#define __INFORMATION_TLV_H__

typedef struct INFORMATION_TLV
{
  unsigned char information_type;
  unsigned char information_length;
  unsigned char oam_version;
  unsigned short revision;
  unsigned char state;
  unsigned char oam_configuration;
  unsigned short oampdu_configuration;
  unsigned char oui [ 3 ];
  unsigned int vendor_specific_info;
} tLVINFORMATION_TLV;




// Routine for packing OAMPDU
//    This routine will allocate heap memory for the packed
//    PDU.
//    Client code to deallocate after use 
unsigned char packINFORMATION_TLV ( tLVINFORMATION_TLV* information_tlv, unsigned int* packedPDUSize, unsigned char** packedINFORMATION_TLV );

// Routine for Unpacking OAMPDU
//    This routine will allocate heap memory for the packed
//    PDU.
//    Client code to deallocate after use 
unsigned char unpackINFORMATION_TLV ( unsigned char* bitstream, unsigned int streamSize, tLVINFORMATION_TLV** unpackedPDU );

//Debug Routines
unsigned char printtLVINFORMATION_TLV ( tLVINFORMATION_TLV* information_tlv );





 #endif


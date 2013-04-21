// THIS IS A GENERATED FILE

// File: OAMPDU.H

#ifndef __OAMPDU_H__
#define __OAMPDU_H__

// Data Structure encapsulating OAMPDU data
typedef struct OAMPDU
{
  unsigned char destination_address [ 6 ];
  unsigned char source_address [ 6 ];
  unsigned short length_type;
  unsigned char subtype;
  unsigned short flags;
  unsigned char code;
  unsigned char* payload;
  unsigned int payload_size;
  unsigned int fcs;
} tlvOAMPDU;

// Routine for packing OAMPDU
// 1. This routine will allocate heap memory for the packed PDU.
//    Client code to deallocate after use
// 2. packedPduSize and packedOAMPDU will be populated by this routine.
//    Client code will declare a NULL pointer variable for packedOAMPDU
//    and send address of the NULL pointer variable to this function
// 3. Return value of 0 indicates success.
unsigned char packOAMPDU   ( tlvOAMPDU* oampdu,
                             unsigned int* packedPduSize,
			     unsigned char** packedOAMPDU );

// Routine for unpacking OAMPDU
// 1. This routine will allocate heap memory for tlvOAMPDU.
//    Client code to deallocate memory after use
// 2. Client code to declare a NULL pointer variable fo unpackedPDU.
//    Upon successful completion of this routine, unpackedPDU will be
//    available with tlvOAMPDU populated using bitstream data
// 3. XML file describing OAMPDU indicates Payload is of variable size.
//    payloadSize indicates size of that data
// 4. Return value of 0 indicates success.
unsigned char unpackOAMPDU ( unsigned char* bitStream,
                             unsigned int   streamSize,
			     tlvOAMPDU**    unpackedPDU );

// Debug Routine for printing bitstream containing OAMPDU
unsigned char printOAMPDU ( unsigned char* bitstream,
                            unsigned int   streamSize );

// Debug Routine for printing tlvOAMPDU
unsigned char printtlvOAMPDU ( tlvOAMPDU* oampdu );

// Debug Routine for hex dump
unsigned char printHexDump ( unsigned char* bitstream,
                             unsigned int   streamSize );

#endif

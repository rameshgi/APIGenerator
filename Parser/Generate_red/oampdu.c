#include "oampdu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>


//------------------------------------------------------------------
unsigned char packOAMPDU ( tlvOAMPDU* oampdu,
                             unsigned int* packedPduSize,
			     unsigned char** packedOAMPDU )

{
  int allocSize = 0;
  
  printf ( "[OAMPDU] packOAMPDU\n" );

  if ( ( NULL == oampdu ) || ( NULL == packedPduSize ) )
  {
    return 1;
  }

  // Size = 6 + 6 + 2 + 1 + 2 + 1 + Var + 4
  //      = 22 + Var
  *packedPduSize = 22 + oampdu->payload_size;

  if ( NULL == *packedOAMPDU )
  {
    printf ( "packedPduSize = %d\n", *packedPduSize );
    *packedOAMPDU = (char*) malloc ( *packedPduSize );
    if ( NULL == *packedOAMPDU )
    {
      return 1;
    }
  }

  memset ( *packedOAMPDU, '\0', *packedPduSize );

  // Destination Address - 6 Bytes
  memcpy ( *packedOAMPDU, oampdu->destination_address, 6 );
  allocSize += 6;


  // Source Address
  memcpy ( ( *packedOAMPDU + allocSize ), oampdu->source_address, 6 );
  allocSize += 6;

  // Length/Type
  unsigned short length_type = htons ( oampdu->length_type );
  memcpy ( ( *packedOAMPDU + allocSize ), &length_type, 2 );
  allocSize += 2;

  // Sub Type
  memcpy ( ( *packedOAMPDU + allocSize ), &( oampdu->subtype ), 1 );
  allocSize += 1;

  // Flags
  unsigned short flags = htons ( oampdu->flags );
  memcpy ( ( *packedOAMPDU + allocSize ), &flags, 2 );
  allocSize += 2;

  // Code
  memcpy ( ( *packedOAMPDU + allocSize ), &( oampdu->code ), 1 );
  allocSize += 1;

  // Payload
  memcpy ( ( *packedOAMPDU + allocSize ), 
           oampdu->payload, 
	   oampdu->payload_size );
  allocSize += oampdu->payload_size;

  // FCS
  unsigned int fcs = htonl ( oampdu->fcs );
  memcpy ( ( *packedOAMPDU + allocSize ), &fcs, 4 );
  allocSize += 4;

  if ( allocSize == *packedPduSize )
  {
    return 0;
  }
  
  return 1;
}

//------------------------------------------------------------------
unsigned char unpackOAMPDU ( unsigned char* bitStream,
                             unsigned int   streamSize,
			     tlvOAMPDU**    unpackedPDU )
{
  int allocSize = 0;

  printf ( "[OAMPDU] unpackOAMPDU\n" );

  if ( NULL == *unpackedPDU )
  {
    *unpackedPDU = ( tlvOAMPDU* ) malloc ( sizeof ( tlvOAMPDU ) );
    if ( NULL == *unpackedPDU )
    {
      printf ( "malloc failed\n" );
      return 1;
    }
  }

  if ( NULL == bitStream )
  {
    printf ( "NULL bitStream\n" );
    return 1;
  }


  // true == hasVarSize
  int varSize = streamSize - 22;
  if ( 0 > varSize )
  {
    return 1;
  }
  
  memset ( *unpackedPDU, '\0', sizeof ( tlvOAMPDU ) );

  // Destination Address
  memcpy ( ( *unpackedPDU )->destination_address, bitStream, 6 );
  allocSize += 6;

  // Source Address
  memcpy ( ( *unpackedPDU )->source_address, ( bitStream + allocSize ), 6 );
  allocSize += 6;

  // Length/Type
  memcpy ( & ( ( *unpackedPDU )->length_type ), 
                          ( bitStream + allocSize ), 2 );
  ( **unpackedPDU ).length_type = ntohs ( ( **unpackedPDU ).length_type );
  allocSize += 2;

  // SubType
  memcpy ( & ( ( *unpackedPDU )->subtype ), ( bitStream + allocSize ), 1 );
  allocSize += 1;

  // Flags
  memcpy ( & ( ( *unpackedPDU )->flags ), ( bitStream + allocSize ), 2 );
  ( **unpackedPDU ).flags = ntohs ( ( **unpackedPDU ).flags );
  allocSize += 2;

  // Code
  memcpy ( & ( ( *unpackedPDU )->code ), ( bitStream + allocSize ), 1 );
  allocSize += 1;

  // Payload
  ( *unpackedPDU )->payload = ( char* ) malloc ( varSize );
  memcpy ( ( *unpackedPDU )->payload, ( bitStream + allocSize ), varSize );
  ( **unpackedPDU ).payload_size = varSize;
  allocSize += varSize;

  // FCS
  memcpy ( & ( ( *unpackedPDU )->fcs ), ( bitStream + allocSize ), 4 );
  ( **unpackedPDU ).fcs = ntohl ( ( **unpackedPDU ).fcs );
  allocSize += 4;

  return 0;
}


//------------------------------------------------------------------
unsigned char printOAMPDU ( unsigned char* bitstream,
                            unsigned int   streamSize )
{
  printf ( "[OAMPDU] printOAMPDU\n" );

  for ( int count = 0; count < streamSize; ++count )
  {
    if ( 0 == count % 2 )
    {
      printf ( " " );
    }
    printf ( "%02x", bitstream [ count ] );
  }

  printf ( "\n" );

  return 0;
}

//------------------------------------------------------------------
unsigned char printtlvOAMPDU ( tlvOAMPDU* oampdu )
{
  printf ( "[OAMPDU] printtlvOAMPDU\n" );
  printf ( "{\n" );
  printf ( "  Destination Address %02x:%02x:%02x:%02x:%02x:%02x\n",
              oampdu->destination_address [ 0 ],
              oampdu->destination_address [ 1 ],
              oampdu->destination_address [ 2 ],
              oampdu->destination_address [ 3 ],
              oampdu->destination_address [ 4 ],
              oampdu->destination_address [ 5 ] );

  printf ( "  Source Address %02x:%02x:%02x:%02x:%02x:%02x\n",
              oampdu->source_address [ 0 ],
              oampdu->source_address [ 1 ],
              oampdu->source_address [ 2 ],
              oampdu->source_address [ 3 ],
              oampdu->source_address [ 4 ],
              oampdu->source_address [ 5 ] );
  
  printf ( "  Length/Type 0x%02x\n", oampdu->length_type );
  printf ( "  SubType 0x%02x\n", oampdu->subtype );
  printf ( "  Flags   0x%02x\n", oampdu->flags );
  printf ( "  Code    0x%02x\n", oampdu->code );
  printf ( "  Payload " );
  for ( int count = 0; count < oampdu->payload_size; ++count )
  {
    if ( 0 == count % 2 )
    {
      printf ( " 0x" );
    }
    printf ( "%02x", oampdu->payload [ count ] );
  }
  printf ( "\n" );
  printf ( "  FCS 0x%02x\n", oampdu->fcs );

  printf ( "}\n" );
  return 0;
}


//------------------------------------------------------------------
unsigned char printHexDump ( unsigned char* bitstream,
                             unsigned int   streamSize )
{
  printf ( "[OAMPDU] printHexDump\n" );
  return 0;
}


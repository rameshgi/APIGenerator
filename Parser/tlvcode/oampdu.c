// THIS IS A GENERATED FILE

#include "oampdu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

//-------------------------------------
unsigned char packOAMPDU ( tLVOAMPDU* oampdu, unsigned int* packedPduSize, unsigned char** packedOAMPDU)
{
  int allocSize = 0;

  if ( ( NULL == oampdu ) || ( NULL == packedPduSize ) )
  {
   return 1;
  }

  *packedPduSize = 22 + oampdu->payload_size;

  if ( NULL == *packedOAMPDU )
  {
    *packedOAMPDU = (char*) malloc ( *packedPduSize );
    if ( NULL == *packedOAMPDU )
    {
      return 1; 
    }
  }

  memset ( *packedOAMPDU, '\0', *packedPduSize );

  // Destination Address
  memcpy ( ( *packedOAMPDU + allocSize ), oampdu->destination_address, 6 );
  allocSize += 6;

  // Source Address
  memcpy ( ( *packedOAMPDU + allocSize ), oampdu->source_address, 6 );
  allocSize += 6;

  // Length/Type
  unsigned short lengthtype = htons ( oampdu->lengthtype );
  memcpy ( ( *packedOAMPDU + allocSize ), &lengthtype, 2 );
  allocSize += 2;

  // SubType
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
  memcpy ( ( *packedOAMPDU + allocSize ), oampdu->payload, oampdu->payload_size );
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

//-------------------------------------
unsigned char unpackOAMPDU ( unsigned char* bitStream,  unsigned int streamSize, tLVOAMPDU** unpackedPDU )
{
  int allocSize = 0;

  if ( NULL == bitStream )
  {
    return 1;
  }

  if ( NULL == *unpackedPDU )
  {
    *unpackedPDU = ( tLVOAMPDU* ) malloc ( sizeof ( tLVOAMPDU ) );
    if ( NULL == *unpackedPDU )
    {
      return 1;
    }
  }

  int varSize = streamSize - 22;
  if ( 0 > varSize )
  {
    return 1;
  }

  memset ( *unpackedPDU, '\0', sizeof ( tLVOAMPDU ) );

  // Destination Address
  memcpy ( ( *unpackedPDU )->destination_address, ( bitStream + allocSize ), 6 );
  allocSize += 6;

  // Source Address
  memcpy ( ( *unpackedPDU )->source_address, ( bitStream + allocSize ), 6 );
  allocSize += 6;

  // Length/Type
  memcpy ( & ( ( *unpackedPDU )->lengthtype ), ( bitStream + allocSize ), 2 );
  ( **unpackedPDU ).lengthtype = ntohs ( ( **unpackedPDU ).lengthtype );
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


//-------------------------------------
unsigned char printtLVOAMPDU ( tLVOAMPDU* oampdu )
{
  printf ( "PRINT tLVOAMPDU\n" );
  printf ( "  Destination Address %02x:%02x:%02x:%02x:%02x:%02x\n", oampdu->destination_address [ 0 ] , oampdu->destination_address [ 1 ] , oampdu->destination_address [ 2 ] , oampdu->destination_address [ 3 ] , oampdu->destination_address [ 4 ] , oampdu->destination_address [ 5 ]  );
  printf ( "  Source Address %02x:%02x:%02x:%02x:%02x:%02x\n", oampdu->source_address [ 0 ] , oampdu->source_address [ 1 ] , oampdu->source_address [ 2 ] , oampdu->source_address [ 3 ] , oampdu->source_address [ 4 ] , oampdu->source_address [ 5 ]  );
  printf ( "  Length/Type %02x\n", oampdu->lengthtype );
  printf ( "  SubType %02x\n", oampdu->subtype );
  printf ( "  Flags %02x\n", oampdu->flags );
  printf ( "  Code %02x\n", oampdu->code );
  printf ( "  Payload " );
  for ( int count = 0; count < oampdu->payload_size; ++count )
  {
    printf ( "%02x", oampdu->payload [ count ]  );
  }
  printf ( "\n" );
  printf ( "  FCS %02x\n", oampdu->fcs );
  return 0;
}

// THIS IS A GENERATED FILE

#include "wimax_mac_frame.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

//-------------------------------------
unsigned char packWIMAX_MAC_FRAME ( tLVWIMAX_MAC_FRAME* wimax_mac_frame, unsigned int* packedPduSize, unsigned char** packedWIMAX_MAC_FRAME)
{
  int allocSize = 0;

  if ( ( NULL == wimax_mac_frame ) || ( NULL == packedPduSize ) )
  {
   return 1;
  }

  *packedPduSize = 46;

  if ( NULL == *packedWIMAX_MAC_FRAME )
  {
    *packedWIMAX_MAC_FRAME = (char*) malloc ( *packedPduSize );
    if ( NULL == *packedWIMAX_MAC_FRAME )
    {
      return 1; 
    }
  }

  memset ( *packedWIMAX_MAC_FRAME, '\0', *packedPduSize );

  // HT
  memcpy ( ( *packedWIMAX_MAC_FRAME + allocSize ), &( wimax_mac_frame->ht ), 1 );
  allocSize += 1;

  // EC
  memcpy ( ( *packedWIMAX_MAC_FRAME + allocSize ), &( wimax_mac_frame->ec ), 1 );
  allocSize += 1;

  // Type
  memcpy ( ( *packedWIMAX_MAC_FRAME + allocSize ), wimax_mac_frame->type, 6 );
  allocSize += 6;

  // ESF
  memcpy ( ( *packedWIMAX_MAC_FRAME + allocSize ), &( wimax_mac_frame->esf ), 1 );
  allocSize += 1;

  // CI
  memcpy ( ( *packedWIMAX_MAC_FRAME + allocSize ), &( wimax_mac_frame->ci ), 1 );
  allocSize += 1;

  // EKS
  memcpy ( ( *packedWIMAX_MAC_FRAME + allocSize ), &( wimax_mac_frame->eks ), 1 );
  allocSize += 1;

  // LEN
  memcpy ( ( *packedWIMAX_MAC_FRAME + allocSize ), wimax_mac_frame->len, 11 );
  allocSize += 11;

  // CID
  memcpy ( ( *packedWIMAX_MAC_FRAME + allocSize ), wimax_mac_frame->cid, 16 );
  allocSize += 16;

  // HCS
  unsigned long long hcs = htonl ( wimax_mac_frame->hcs );
  memcpy ( ( *packedWIMAX_MAC_FRAME + allocSize ), &hcs, 8 );
  allocSize += 8;

  if ( allocSize == *packedPduSize )
  {
    return 0;
  }

  return 1;

}

//-------------------------------------
unsigned char unpackWIMAX_MAC_FRAME ( unsigned char* bitStream,  unsigned int streamSize, tLVWIMAX_MAC_FRAME** unpackedPDU )
{
  int allocSize = 0;

  if ( NULL == bitStream )
  {
    return 1;
  }

  if ( NULL == *unpackedPDU )
  {
    *unpackedPDU = ( tLVWIMAX_MAC_FRAME* ) malloc ( sizeof ( tLVWIMAX_MAC_FRAME ) );
    if ( NULL == *unpackedPDU )
    {
      return 1;
    }
  }

  memset ( *unpackedPDU, '\0', sizeof ( tLVWIMAX_MAC_FRAME ) );

  // HT
  memcpy ( & ( ( *unpackedPDU )->ht ), ( bitStream + allocSize ), 1 );
  allocSize += 1;

  // EC
  memcpy ( & ( ( *unpackedPDU )->ec ), ( bitStream + allocSize ), 1 );
  allocSize += 1;

  // Type
  memcpy ( ( *unpackedPDU )->type, ( bitStream + allocSize ), 6 );
  allocSize += 6;

  // ESF
  memcpy ( & ( ( *unpackedPDU )->esf ), ( bitStream + allocSize ), 1 );
  allocSize += 1;

  // CI
  memcpy ( & ( ( *unpackedPDU )->ci ), ( bitStream + allocSize ), 1 );
  allocSize += 1;

  // EKS
  memcpy ( & ( ( *unpackedPDU )->eks ), ( bitStream + allocSize ), 1 );
  allocSize += 1;

  // LEN
  memcpy ( ( *unpackedPDU )->len, ( bitStream + allocSize ), 11 );
  allocSize += 11;

  // CID
  memcpy ( ( *unpackedPDU )->cid, ( bitStream + allocSize ), 16 );
  allocSize += 16;

  // HCS
  memcpy ( & ( ( *unpackedPDU )->hcs ), ( bitStream + allocSize ), 8 );
  ( **unpackedPDU ).hcs = ntohl ( ( **unpackedPDU ).hcs );
  allocSize += 8;

  return 0;
}


//-------------------------------------
unsigned char printtLVWIMAX_MAC_FRAME ( tLVWIMAX_MAC_FRAME* wimax_mac_frame )
{
  printf ( "PRINT tLVWIMAX_MAC_FRAME\n" );
  printf ( "  HT %02x\n", wimax_mac_frame->ht );
  printf ( "  EC %02x\n", wimax_mac_frame->ec );
  printf ( "  Type %02x:%02x:%02x:%02x:%02x:%02x\n", wimax_mac_frame->type [ 0 ] , wimax_mac_frame->type [ 1 ] , wimax_mac_frame->type [ 2 ] , wimax_mac_frame->type [ 3 ] , wimax_mac_frame->type [ 4 ] , wimax_mac_frame->type [ 5 ]  );
  printf ( "  ESF %02x\n", wimax_mac_frame->esf );
  printf ( "  CI %02x\n", wimax_mac_frame->ci );
  printf ( "  EKS %02x\n", wimax_mac_frame->eks );
  printf ( "  LEN %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n", wimax_mac_frame->len [ 0 ] , wimax_mac_frame->len [ 1 ] , wimax_mac_frame->len [ 2 ] , wimax_mac_frame->len [ 3 ] , wimax_mac_frame->len [ 4 ] , wimax_mac_frame->len [ 5 ] , wimax_mac_frame->len [ 6 ] , wimax_mac_frame->len [ 7 ] , wimax_mac_frame->len [ 8 ] , wimax_mac_frame->len [ 9 ] , wimax_mac_frame->len [ 10 ]  );
  printf ( "  CID %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n", wimax_mac_frame->cid [ 0 ] , wimax_mac_frame->cid [ 1 ] , wimax_mac_frame->cid [ 2 ] , wimax_mac_frame->cid [ 3 ] , wimax_mac_frame->cid [ 4 ] , wimax_mac_frame->cid [ 5 ] , wimax_mac_frame->cid [ 6 ] , wimax_mac_frame->cid [ 7 ] , wimax_mac_frame->cid [ 8 ] , wimax_mac_frame->cid [ 9 ] , wimax_mac_frame->cid [ 10 ] , wimax_mac_frame->cid [ 11 ] , wimax_mac_frame->cid [ 12 ] , wimax_mac_frame->cid [ 13 ] , wimax_mac_frame->cid [ 14 ] , wimax_mac_frame->cid [ 15 ]  );
  printf ( "  HCS %llu\n", wimax_mac_frame->hcs );
  return 0;
}

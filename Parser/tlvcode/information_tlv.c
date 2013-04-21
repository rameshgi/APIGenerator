// THIS IS A GENERATED FILE

#include "information_tlv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

//-------------------------------------
unsigned char packINFORMATION_TLV ( tLVINFORMATION_TLV* information_tlv, unsigned int* packedPduSize, unsigned char** packedINFORMATION_TLV)
{
  int allocSize = 0;

  if ( ( NULL == information_tlv ) || ( NULL == packedPduSize ) )
  {
   return 1;
  }

  *packedPduSize = 16;

  if ( NULL == *packedINFORMATION_TLV )
  {
    *packedINFORMATION_TLV = (char*) malloc ( *packedPduSize );
    if ( NULL == *packedINFORMATION_TLV )
    {
      return 1; 
    }
  }

  memset ( *packedINFORMATION_TLV, '\0', *packedPduSize );

  // Information Type
  memcpy ( ( *packedINFORMATION_TLV + allocSize ), &( information_tlv->information_type ), 1 );
  allocSize += 1;

  // Information Length
  memcpy ( ( *packedINFORMATION_TLV + allocSize ), &( information_tlv->information_length ), 1 );
  allocSize += 1;

  // OAM Version
  memcpy ( ( *packedINFORMATION_TLV + allocSize ), &( information_tlv->oam_version ), 1 );
  allocSize += 1;

  // Revision
  unsigned short revision = htons ( information_tlv->revision );
  memcpy ( ( *packedINFORMATION_TLV + allocSize ), &revision, 2 );
  allocSize += 2;

  // State
  memcpy ( ( *packedINFORMATION_TLV + allocSize ), &( information_tlv->state ), 1 );
  allocSize += 1;

  // OAM Configuration
  memcpy ( ( *packedINFORMATION_TLV + allocSize ), &( information_tlv->oam_configuration ), 1 );
  allocSize += 1;

  // OAMPDU Configuration
  unsigned short oampdu_configuration = htons ( information_tlv->oampdu_configuration );
  memcpy ( ( *packedINFORMATION_TLV + allocSize ), &oampdu_configuration, 2 );
  allocSize += 2;

  // OUI
  memcpy ( ( *packedINFORMATION_TLV + allocSize ), information_tlv->oui, 3 );
  allocSize += 3;

  // Vendor Specific Info
  unsigned int vendor_specific_info = htonl ( information_tlv->vendor_specific_info );
  memcpy ( ( *packedINFORMATION_TLV + allocSize ), &vendor_specific_info, 4 );
  allocSize += 4;

  if ( allocSize == *packedPduSize )
  {
    return 0;
  }

  return 1;

}

//-------------------------------------
unsigned char unpackINFORMATION_TLV ( unsigned char* bitStream,  unsigned int streamSize, tLVINFORMATION_TLV** unpackedPDU )
{
  int allocSize = 0;

  if ( NULL == bitStream )
  {
    return 1;
  }

  if ( NULL == *unpackedPDU )
  {
    *unpackedPDU = ( tLVINFORMATION_TLV* ) malloc ( sizeof ( tLVINFORMATION_TLV ) );
    if ( NULL == *unpackedPDU )
    {
      return 1;
    }
  }

  memset ( *unpackedPDU, '\0', sizeof ( tLVINFORMATION_TLV ) );

  // Information Type
  memcpy ( & ( ( *unpackedPDU )->information_type ), ( bitStream + allocSize ), 1 );
  allocSize += 1;

  // Information Length
  memcpy ( & ( ( *unpackedPDU )->information_length ), ( bitStream + allocSize ), 1 );
  allocSize += 1;

  // OAM Version
  memcpy ( & ( ( *unpackedPDU )->oam_version ), ( bitStream + allocSize ), 1 );
  allocSize += 1;

  // Revision
  memcpy ( & ( ( *unpackedPDU )->revision ), ( bitStream + allocSize ), 2 );
  ( **unpackedPDU ).revision = ntohs ( ( **unpackedPDU ).revision );
  allocSize += 2;

  // State
  memcpy ( & ( ( *unpackedPDU )->state ), ( bitStream + allocSize ), 1 );
  allocSize += 1;

  // OAM Configuration
  memcpy ( & ( ( *unpackedPDU )->oam_configuration ), ( bitStream + allocSize ), 1 );
  allocSize += 1;

  // OAMPDU Configuration
  memcpy ( & ( ( *unpackedPDU )->oampdu_configuration ), ( bitStream + allocSize ), 2 );
  ( **unpackedPDU ).oampdu_configuration = ntohs ( ( **unpackedPDU ).oampdu_configuration );
  allocSize += 2;

  // OUI
  memcpy ( ( *unpackedPDU )->oui, ( bitStream + allocSize ), 3 );
  allocSize += 3;

  // Vendor Specific Info
  memcpy ( & ( ( *unpackedPDU )->vendor_specific_info ), ( bitStream + allocSize ), 4 );
  ( **unpackedPDU ).vendor_specific_info = ntohl ( ( **unpackedPDU ).vendor_specific_info );
  allocSize += 4;

  return 0;
}


//-------------------------------------
unsigned char printtLVINFORMATION_TLV ( tLVINFORMATION_TLV* information_tlv )
{
  printf ( "PRINT tLVINFORMATION_TLV\n" );
  printf ( "  Information Type %02x\n", information_tlv->information_type );
  printf ( "  Information Length %02x\n", information_tlv->information_length );
  printf ( "  OAM Version %02x\n", information_tlv->oam_version );
  printf ( "  Revision %02x\n", information_tlv->revision );
  printf ( "  State %02x\n", information_tlv->state );
  printf ( "  OAM Configuration %02x\n", information_tlv->oam_configuration );
  printf ( "  OAMPDU Configuration %02x\n", information_tlv->oampdu_configuration );
  printf ( "  OUI %02x:%02x:%02x\n", information_tlv->oui [ 0 ] , information_tlv->oui [ 1 ] , information_tlv->oui [ 2 ]  );
  printf ( "  Vendor Specific Info %02x\n", information_tlv->vendor_specific_info );
  return 0;
}

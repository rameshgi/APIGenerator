#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>


int foo ( char** ptr, int* size )
{
  static int count = 0;
  if ( NULL == *ptr )
  {
    *ptr  = ( char* ) malloc ( 6 );
  }

  char p [ 6 ] = "Rames\0";
  char p1[ 6 ] = "Sangi\0";
  memset ( *ptr, '\0', 6 );

  if ( 0 != count )
  {
    memcpy ( p, p1, 6 );
  }

  ++count;

    *( *ptr + 0 ) = p [ 0 ];
    *( *ptr + 1 ) = p [ 1 ];
    *( *ptr + 2 ) = p [ 2 ];
    *( *ptr + 3 ) = p [ 3 ];
    *( *ptr + 4 ) = p [ 4 ];
    *( *ptr + 5 ) = p [ 5 ];

  return 0;
}

int main ()
{
  char* ptr  = NULL;
  int   size = 0;
  foo ( &ptr, &size );

  for ( size = 0; size < 6; ++size )
  {
    printf ( "%c @ %u\n", *( ptr + size ), ( unsigned int )( ptr + size ) );
  }

  foo ( &ptr, &size );
  for ( size = 0; size < 6; ++size )
  {
    printf ( "%c @ %u\n", *( ptr + size ), ( unsigned int )( ptr + size ) );
  }

  unsigned long a = 0;
  printf ( "%u long\n", sizeof ( a ) );

  unsigned long long b = 0xAABBCCDD11223344;
  b = htonl ( b );
  printf ( "%llu long long\n", b );
  unsigned int bb, bc = 0;
  memcpy ( &bb, &b, sizeof (int) );
  memcpy ( &bc, (&b+8), sizeof (int) );
  printf ( "%02x_%02x long long\n", bb, bc);
  b = ntohl ( b );
  printf ( "%llu long long\n", b );
  bb = 0; bc = 0;
  memcpy ( &bb, &b, sizeof (int) );
  memcpy ( &bc, (&b+8), sizeof (int) );
  printf ( "%02x_%02x long long\n", bb, bc);

  b = ntohl ( b );
  printf ( "%llu long long\n", b );

  int endian = 1;
  char *p = ( char* ) &endian;

  printf ( "Endian %02x:%02x:%02x:%02x\n", 
           p [ 0 ], p [ 1 ], p [ 2 ], p [ 3 ] );

  endian = endian << 1;
  printf ( "Endian %02x:%02x:%02x:%02x\n", 
           p [ 0 ], p [ 1 ], p [ 2 ], p [ 3 ] );
}

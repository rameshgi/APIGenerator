// THIS IS A GENERATED FILE

#include <stdio.h>

unsigned char printHexDump ( unsigned char* bitstream, unsigned int streamSize )
{
  for ( int count = 0; count < streamSize; ++count )
  {
    if ( 0 == count%2 )
    {
      printf ( " " );
    }    printf ( "%02x",bitstream [ count ] );
  }  printf ( "\n" );

  return 0;
}

import java.io.*;

public class TLVCodeGen
{

  public static StringBuffer utilVarSizeStr;
  public static String outputPath;

  public static void main ( String args [] )
  {
    utilVarSizeStr = new StringBuffer ();
    TLVCodeGenData xmlData     = new TLVCodeGenData ();
    TLVCodeGenXMLParser parser = new TLVCodeGenXMLParser ( xmlData );
    outputPath = new String 
                ( "/home/ramesh/Tech/Projects/TLVCodeGen/Parser/tlvcode/" );

    try
    {
      parser.parse ();
      TLVCodeGenXMLDefaultHandler.printData ( xmlData );
      generateHeaderFile ( xmlData );
      generateCFile      ( xmlData );
      // generateUtilFile   ();
    }
    catch ( Exception e )
    {
      System.out.println ( "Exception - " + e.toString () );
    }
  }

  public static int generateHeaderFile ( TLVCodeGenData xmlData )
  {

    // Each PDU in separate file
    if ( !xmlData._pdu.isEmpty () )
    {
      for ( int index = 0; index < xmlData._pdu.size (); ++index )
      {
        PDUDef pdu = xmlData._pdu.get ( index );
        StringBuffer hFileContent = new StringBuffer ();
	String       hdrName      = TLVUtil.formatVariableName
	                                        ( pdu._pduName, true );
	String structName         = TLVUtil.getStructName ( pdu._pduName );

	// Create File
	StringBuffer hdrFileName  = new StringBuffer
	                            ( outputPath + hdrName.toLowerCase () +
				      ".h" );
	try
	{
	  File hdrFile              = new File ( hdrFileName.toString () );
	  hdrFile.setWritable ( true );
	  FileWriter hdrFileWriter  = new FileWriter ( hdrFile, false );

          // Standard stuff here - TODO file header
	  hFileContent.append ( "// THIS IS A GENERATED FILE\n\n" );

          // Make sure to #include only once
	  hFileContent.append ( "#ifndef " +
	                        "__"       + 
	                        hdrName    +
	  		        "_H__\n" );
	  hFileContent.append ( "#define " +
	                        "__"       +
	  		        hdrName    +
			        "_H__\n\n" );

          // Define the Data Structure encapsulating all PDU Fields
          // This Data Structure will be used by the call processing modules
	  hFileContent.append ( "typedef struct " + 
	                        hdrName           +
	    	                "\n" + "{\n" );
	

          for ( int field = 0; field < pdu._field.size (); ++field )
          {
            PDUField pduField = pdu._field.get ( field );
	    String   varName  = TLVUtil.formatVariableName
	                               ( pduField._fieldName, false );
	    // append data type
	  
	    // TODO add if ( !subtype ) here
	    hFileContent.append ( "  " + TLVUtil.determineDataType
	                               ( pduField._length ) );
	    hFileContent.append ( " " + varName );
	    if ( TLVUtil.isArray ( pduField._length ) )
	    {
              hFileContent.append ( " [ " + pduField._length + " ]" );
	    }
	    hFileContent.append ( ";\n" );

	    // if VAR == length, add field to indicate size
	    if ( pduField._length.equalsIgnoreCase ( "VAR" ) )
	    {
	      hFileContent.append ( "  unsigned int " +
	                          varName           +
	  			  "_size"           +
				  ";\n" );

	      utilVarSizeStr.append ( " + " + 
	                            hdrName.toLowerCase () +
				    "->" +
				    varName +
				    "_size" );
	    }
          }
          hFileContent.append ( "} " + structName + ";\n" );

	  // Add Routines here
	  hFileContent.append ( "\n\n\n\n" );
	  hFileContent.append 
	  ( "// Routine for packing OAMPDU\n" +
            "//    This routine will allocate heap memory for the packed\n" +
	    "//    PDU.\n" +
            "//    Client code to deallocate after use \n" );

	  hFileContent.append ( "unsigned char pack"                 + 
	                      hdrName                              +
	                      " ( "                                + 
			      structName                           + 
			      "* "                                 +
			      hdrName.toLowerCase ()               +
			      ", unsigned int* packedPDUSize,"     +
			      " unsigned char** packed"            +
			      hdrName                              +
			      " );\n\n" );

	  hFileContent.append 
	  ( "// Routine for Unpacking OAMPDU\n" +
          "//    This routine will allocate heap memory for the packed\n" +
	  "//    PDU.\n" +
          "//    Client code to deallocate after use \n" );
	  hFileContent.append ( "unsigned char unpack" +
	                      hdrName +
			      " ( unsigned char* bitstream," +
			      " unsigned int streamSize," +
			      " " +
			      structName +
			      "** unpackedPDU );\n\n" );

	  hFileContent.append ( "//Debug Routines\n" );
	  // hFileContent.append ( "unsigned char print" +
	  //                    hdrName +
	  //   	                " ( unsigned char* bitstream," +
	  //	                " unsigned int streamSize );\n\n" );

	  hFileContent.append ( "unsigned char print" +
	                      structName +
			      " ( " +
			      structName +
			      "* " +
			      hdrName.toLowerCase () +
			      " );\n\n" );


       
          hFileContent.append ( "\n\n\n\n #endif\n\n" );

	  hdrFileWriter.write ( hFileContent.toString () );
	  hdrFileWriter.flush ();
	}
	catch ( Exception e )
	{
          System.out.println ( "FILE WRITE ERROR :" + e.toString () );
	}
        //System.out.println ( hFileContent.toString () );
      }
    }

    return 0;
  }

  public static int generateUtilFile ()
  {
    StringBuffer hUtilContent = new StringBuffer ();
    StringBuffer cUtilContent = new StringBuffer ();

    StringBuffer hUtilFileName = new StringBuffer ( outputPath +
                                                    "util.h" );
    StringBuffer cUtilFileName = new StringBuffer ( outputPath +
                                                    "util.c" );

    hUtilContent.append ( "// THIS IS A GENERATED FILE\n\n" );
    hUtilContent.append ("unsigned char printHexDump" +
	                     " ( unsigned char* bitstream," +
			     " unsigned int streamSize );\n\n" );

    
    cUtilContent.append ( "// THIS IS A GENERATED FILE\n\n" );

    cUtilContent.append ( "#include <stdio.h>\n\n" );
    cUtilContent.append ( "unsigned char printHexDump" +
                           " ( unsigned char* bitstream, " +
			   "unsigned int streamSize )\n{\n" );

    cUtilContent.append ( "  for ( int count = 0; " +
                           "count < streamSize; ++count )\n  {\n" );
    cUtilContent.append ( "    if ( 0 == count%2 )\n    {\n" );
    cUtilContent.append ( "      printf ( \" \" );\n    }" );
    cUtilContent.append ( "    printf ( \"%02x\"," +
                           "bitstream [ count ] );\n  }" );
    cUtilContent.append ( "  printf ( \"\\n\" );\n\n" );
    cUtilContent.append ( "  return 0;\n" );
    cUtilContent.append ( "}\n" );

    try
    {
      File hUtilFile = new File ( hUtilFileName.toString () );
      hUtilFile.setWritable ( true );
      FileWriter hUtilWriter = new FileWriter ( hUtilFile );
      hUtilWriter.write ( hUtilContent.toString () );
      hUtilWriter.flush ();

      File cUtilFile = new File ( cUtilFileName.toString () );
      cUtilFile.setWritable ( true );
      FileWriter cUtilWriter = new FileWriter ( cUtilFile );
      cUtilWriter.write ( cUtilContent.toString () );
      cUtilWriter.flush ();
    }
    catch ( Exception e )
    {
      System.out.println ( e.toString () );
    }

    return 0;
  }

  public static int generateCFile ( TLVCodeGenData xmlData )
  {
    // Each PDU in separate file
    if ( !xmlData._pdu.isEmpty () )
    {
      for ( int index = 0; index < xmlData._pdu.size (); ++index )
      {
        PDUDef pdu = xmlData._pdu.get ( index );
        StringBuffer cFileContent = new StringBuffer ();
	String       hdrName      = TLVUtil.formatVariableName
	                                        ( pdu._pduName, true );
	String structName         = TLVUtil.getStructName ( pdu._pduName );
	String structVariable     = hdrName.toLowerCase ();
	String sizeVariable       = new String ( "packedPduSize" );
	String packVariable       = new String ( "packed" + hdrName );

	StringBuffer cFileName  = new StringBuffer
	                            ( outputPath + hdrName.toLowerCase () +
				      ".c" );
	try
	{
	  File cFile              = new File ( cFileName.toString () );
	  cFile.setWritable ( true );
	  FileWriter cFileWriter  = new FileWriter ( cFile, false );
	  cFile.setWritable ( true );

          // Standard stuff here - TODO file header
	  cFileContent.append ( "// THIS IS A GENERATED FILE\n\n" );

	  // all #include
	  cFileContent.append ( "#include \"" + 
	                      structVariable +
			      ".h\"\n" );
	  cFileContent.append ( "#include <stdio.h>\n" );
	  cFileContent.append ( "#include <stdlib.h>\n" );
	  cFileContent.append ( "#include <string.h>\n" );
	  cFileContent.append ( "#include <arpa/inet.h>\n\n" );

	  // Function - Pack
	  cFileContent.append ( "//-------------------------------------\n" );
	  cFileContent.append ( "unsigned char pack" +
	                      hdrName +
			      " ( " +
			      structName +
			      "* " +
			      structVariable +
			      ", unsigned int* " +
			      sizeVariable +
			      ", unsigned char** " +
			      packVariable +
			      ")\n" );
	  cFileContent.append ( "{\n" );
          cFileContent.append ( "  int allocSize = 0;\n\n" );

          // Add Sanity Checks on input
          cFileContent.append ( "  if ( ( NULL == " +
	                      structVariable +
			      " ) || ( NULL == " +
			      sizeVariable +
			      " ) )\n" );
	  cFileContent.append ( "  {\n   return 1;\n  }\n\n" );

          // Size
	  cFileContent.append 
	       ( "  *" +
	         sizeVariable +
	         " = " +
		 Integer.toString ( pdu._sizeOfConstFields ) +
		 utilVarSizeStr +
		 ";\n\n" );

          utilVarSizeStr = new StringBuffer ();

          // Mem allocation
	  cFileContent.append ( "  if ( NULL == *" +
	                      packVariable +
	                      " )\n  {\n" );
	  cFileContent.append ( "    *" + packVariable +
	                      " = (char*) malloc ( *" +
			      sizeVariable + " );\n" );
	  cFileContent.append ( "    if ( NULL == *" + packVariable + " )\n" );
	  cFileContent.append ( "    {\n      return 1; \n    }\n  }\n\n" );

	  // Mem initialization
	  cFileContent.append ( "  memset ( *" +
	                      packVariable +
			      ", '\\0', *" +
			      sizeVariable +
			      " );\n\n" );

	  // Actual Packing
          for ( int field = 0; field < pdu._field.size (); ++field )
	  {
            PDUField pduField = pdu._field.get ( field );
            String tempVar = TLVUtil.formatVariableName 
	                             ( pduField._fieldName, false );
	    boolean endianCheckReqd = false;
	  
	    cFileContent.append ( "  // " + pduField._fieldName + "\n" );
	    // Endian-ness
            if ( pduField._length.equalsIgnoreCase ( "2" ) ||
	         pduField._length.equalsIgnoreCase ( "4" ) ||
	         pduField._length.equalsIgnoreCase ( "8" ) )
	    {
	      endianCheckReqd = true;
              cFileContent.append 
	        ( "  " + TLVUtil.determineDataType ( pduField._length ) +
		  " " +
		  tempVar +
		  " = " +
		  TLVUtil.determineEndianOp ( pduField._length, true ) +
		  " ( " + structVariable + "->" +
		  tempVar +
		  " );\n" );
	    }

            cFileContent.append ( "  memcpy ( ( *" +
	                        packVariable + " + allocSize ), " );
	    if ( TLVUtil.isArray ( pduField._length ) ||
	         pduField._length.equalsIgnoreCase ( "VAR" ) )
	    {
              cFileContent.append ( structVariable + "->" + tempVar + ", " );
	    }
	    else
	    {
              if ( endianCheckReqd )
	      {
                cFileContent.append ( "&" + tempVar + ", " );
	      }
	      else
	      {
                cFileContent.append ( "&( " + structVariable + "->" +
	                              tempVar + " ), " );
	      }
	    }

            if ( pduField._length.equalsIgnoreCase ( "VAR" ) )
	    {
              cFileContent.append ( structVariable + "->" +
	                          tempVar + "_size" + " );\n" );
	      cFileContent.append ( "  allocSize += " +
	                          structVariable + "->" +
				  tempVar + "_size" +
				  ";\n\n" );
	    }
	    else
	    {
	      cFileContent.append ( pduField._length + " );\n" );
	      cFileContent.append ( "  allocSize += " + pduField._length +
	                        ";\n\n" );
	    }
	  }

	  // Size check
	  cFileContent.append ( "  if ( allocSize == *" + sizeVariable +
	                      " )\n  {\n    return 0;\n  }\n\n" );

	  cFileContent.append ( "  return 1;\n\n" );

	  cFileContent.append ( "}\n\n" );

          // Function - Unpack
	  cFileContent.append ( "//-------------------------------------\n" );
	  cFileContent.append ( "unsigned char unpack" +
	                      hdrName                +
			      " ( unsigned char* bitStream, " +
			      " unsigned int streamSize, " +
			      structName + "** unpackedPDU )\n" );
	  cFileContent.append ( "{\n  int allocSize = 0;\n\n" );

	  // Sanity Check
	  cFileContent.append ( "  if ( NULL == bitStream )\n  {\n" +
	                      "    return 1;\n  }\n\n" );
        
	  // mem alloc
	  cFileContent.append ( "  if ( NULL == *unpackedPDU )\n" +
	                      "  {\n" +
			      "    *unpackedPDU = ( " + structName +
			      "* ) malloc ( sizeof ( " + structName +
			      " ) );\n" );
	  cFileContent.append ( "    if ( NULL == *unpackedPDU )\n    {\n" +
	                      "      return 1;\n    }\n  }\n\n" );

	  if ( pdu._hasVarData )
	  {
            cFileContent.append ( "  int varSize = streamSize - " +
	                        pdu._sizeOfConstFields + ";\n" );
	    cFileContent.append ( "  if ( 0 > varSize )\n  {\n" +
	                        "    return 1;\n  }\n\n" );

	  }

          // Mem init
          cFileContent.append ( "  memset ( *unpackedPDU, '\\0', " +
	                      "sizeof ( " + structName + " ) );\n\n" );

          // Actual Unpack
	  for ( int field = 0; field < pdu._field.size (); ++field )
	  {
            PDUField pduField = pdu._field.get ( field );
	    String tempVar = TLVUtil.formatVariableName 
	                             ( pduField._fieldName, false );
	    StringBuffer tempStr    = new StringBuffer 
	                            ( "( *unpackedPDU )->" + tempVar );
	    boolean endianCheckReqd = false;

	    cFileContent.append ( "  // " + pduField._fieldName + "\n" );

            // Alloc memory for variable fields
	    if ( pduField._length.equalsIgnoreCase ( "VAR" ) )
	    {
              cFileContent.append ( "  " + tempStr +
	                          " = ( char* ) malloc ( varSize );\n" );
	    }

            cFileContent.append ( "  memcpy ( " );

            if ( TLVUtil.isArray ( pduField._length ) )
	    {
              cFileContent.append ( tempStr +
	                          ", ( bitStream + allocSize ), " +
				  pduField._length + " );\n" );
	    }
	    else if ( pduField._length.equalsIgnoreCase ( "VAR" ) )
	    {
              cFileContent.append ( tempStr +
	                          ", ( bitStream + allocSize ), " +
				  "varSize );\n" );
	    }
	    else
	    {
              cFileContent.append ( "& ( " + tempStr + " ), " +
	                          "( bitStream + allocSize ), " +
				  pduField._length + " );\n" );
	    }

	    // Endian-ness
	    if ( pduField._length.equalsIgnoreCase ( "2" ) ||
	         pduField._length.equalsIgnoreCase ( "4" ) ||
	         pduField._length.equalsIgnoreCase ( "8" ) )
	    {
              cFileContent.append ( "  ( **unpackedPDU )." +
	                          TLVUtil.formatVariableName
				    ( pduField._fieldName, false ) +
				  " = " +
				  TLVUtil.determineEndianOp 
				    ( pduField._length, false ) +
				  " ( ( **unpackedPDU )." +
				  TLVUtil.formatVariableName
				    ( pduField._fieldName, false ) +
				  " );\n" );
	    }

            if ( pduField._length.equalsIgnoreCase ( "VAR" ) )
	    {
              cFileContent.append ( "  ( **unpackedPDU )." +
	                          TLVUtil.formatVariableName
				     ( pduField._fieldName, false ) +
				  "_size = varSize;\n" );
	      cFileContent.append ( "  allocSize += varSize;\n\n" );
	    }
            else
	    {
              cFileContent.append ( "  allocSize += " +
	                          pduField._length + ";\n\n" );
	    }
	  }

          cFileContent.append ( "  return 0;\n" );
	  cFileContent.append ( "}\n\n\n" );

	  // Print Data Structure pertaining to this PDU
	  cFileContent.append ( "//-------------------------------------\n" );
          cFileContent.append ( "unsigned char print" +
	                        structName + " ( " +
				structName + "* " +
				structVariable + " )\n" );
	  cFileContent.append ( "{\n" );
          
	  cFileContent.append ( "  printf ( \"PRINT " +
	                        structName + "\\n\" );\n" );
	  
	  for ( int field = 0; field < pdu._field.size (); ++field )
	  {
            StringBuffer whiteSpace = new StringBuffer ();
	    StringBuffer varStack   = new StringBuffer ();
	    StringBuffer varName    = new StringBuffer ();
            PDUField pduField       = pdu._field.get ( field );
	    String fieldName        = TLVUtil.formatVariableName
	                                 ( pduField._fieldName, false );

	    varName.append ( pduField._fieldName );

	    if ( TLVUtil.isArray ( pduField._length ) )
	    {
              for ( int var = 0; 
	            var < Integer.parseInt ( pduField._length );
		    ++var )
	      {
                String indexNum = Integer.toString ( var );
		if ( 0 != var ) 
		{
		  whiteSpace.append ( ":" );
		  varStack.append ( ", " );
		}
		whiteSpace.append ( "%02x" );
                varStack.append ( structVariable + "->" + fieldName +
				  " [ " + indexNum + " ] " );

	      }
	    }
	    else if ( pduField._length.equalsIgnoreCase ( "VAR" ) )
	    {
              whiteSpace.append ( "%02x" );
	      varStack.append ( structVariable + "->" + fieldName +
				  " [ count ] " );
	    }
	    else
	    {
	      if ( pduField._length.equalsIgnoreCase ( "8" ) )
	      {
                whiteSpace.append ( "%llu" );
	      }
	      else
	      {
                whiteSpace.append ( "%02x" );
              }

	      varStack.append ( structVariable + "->" + fieldName );
	    }

            cFileContent.append ( "  printf ( \"  " + varName ); 

	    if ( pduField._length.equalsIgnoreCase ( "VAR" ) )
	    {
	      cFileContent.append ( " \" );\n" );
	      cFileContent.append ( "  for ( int count = 0; " +
	                            "count < " + 
				    structVariable + "->" + fieldName +
				    "_size; ++count )\n  {\n" );
	      cFileContent.append ( "    printf ( \"" +
	                            whiteSpace + "\", " +
				    varStack + " );\n  }\n" );
	      cFileContent.append ( "  printf ( \"\\n\" );\n" );
	    }
	    else
	    {
              cFileContent.append ( " " + whiteSpace + "\\n\", " +
	                            varStack + " );\n" );
	    }
	  }

          cFileContent.append ( "  return 0;\n" );
	  cFileContent.append ( "}\n" );



          // Write to a file
	  cFileWriter.write ( cFileContent.toString () );
	  cFileWriter.flush ();

          //System.out.println ( cFileContent.toString () );
	}
	catch ( Exception e )
	{
          System.out.println ( e.toString () );
	}
      }
    }

    return 0;
  }
}

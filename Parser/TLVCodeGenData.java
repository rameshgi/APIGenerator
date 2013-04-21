import java.util.*;

class TLVUtil
{
  static public String formatVariableName ( String input, boolean isStruct )
  {
    StringBuffer output = new StringBuffer ();

    for ( int count = 0; count < input.length (); ++count )
    {
      char letter = input.charAt ( count );
      if ( Character.isLetterOrDigit ( letter ) )
      {
        output.append ( letter );
      }
      else if ( Character.isWhitespace ( letter ) )
      {
        output.append ( "_" );
      }
    }

    if ( isStruct )
    {
      return output.toString ().toUpperCase ();
    }

    return output.toString ().toLowerCase ();
  }

  static public String getStructName ( String input )
  {
    return new String ( "tLV" + formatVariableName ( input, true ) );
  }

  static public String determineDataType ( String sizeValue )
  {
    // 2 == Size -> unsigned short
    // 4 == Size -> unsigned int
    // 8 == Size -> unsigned long
    // TODO Floating value ??
    // rest == unsigned char

    if ( sizeValue.equalsIgnoreCase ( "2" ) )
    {
      return new String ( "unsigned short" );
    }
    else if ( sizeValue.equalsIgnoreCase ( "4" ) )
    {
      return new String ( "unsigned int" );
    }
    else if ( sizeValue.equalsIgnoreCase ( "8" ) )
    {
      return new String ( "unsigned long long" );
    }
    else if ( sizeValue.equalsIgnoreCase ( "VAR" ) )
    {
      return new String ( "unsigned char*" );
    }
    else
    {
      return new String ( "unsigned char" );
    }
  }

  static public String determineEndianOp ( String length, boolean isPack )
  {
    if ( isPack )
    {
      if ( length.equalsIgnoreCase ( "2" ) )
      {
        return new String ( "htons" );
      }
      else if ( length.equalsIgnoreCase ( "4" ) ||
	        length.equalsIgnoreCase ( "8" ) )
      {
        return new String ( "htonl" );
      }
      else
      {
        return new String ();
      }
    }
    else
    {
      if ( length.equalsIgnoreCase ( "2" ) )
      {
        return new String ( "ntohs" );
      }
      else if ( length.equalsIgnoreCase ( "4" ) ||
	        length.equalsIgnoreCase ( "8" ) )
      {
        return new String ( "ntohl" );
      }
      else
      {
        return new String ();
      }
    }
  }

  static public boolean isArray ( String sizeValue )
  {
    boolean output = true;

    if ( sizeValue.equalsIgnoreCase ( "1" ) ||
         sizeValue.equalsIgnoreCase ( "2" ) ||
         sizeValue.equalsIgnoreCase ( "4" ) ||
	 sizeValue.equalsIgnoreCase ( "8" ) ||
	 sizeValue.equalsIgnoreCase ( "VAR" ) )
    {
      output = false;
    }

    return output;
  }
}

class PDUField
{
  public String	_position;
  public String	_fieldName;
  public String _type;
  public String	_length;
  public String _minLength;
  public String _maxLength;
  public String _defVal;
  public boolean _hasMinLength;
  public boolean _hasMaxLength;

  public PDUField ()
  {
    _position  = new String ();
    _fieldName = new String ();
    _type      = new String ();
    _length    = new String ();
    _minLength = new String ();
    _maxLength = new String ();
    _defVal    = new String ();
    _hasMinLength = false;
    _hasMaxLength = false;
  }
}

class PDUDef
{
  public String _pduName;
  public ArrayList <PDUField> _field;
  public int _sizeOfConstFields;
  public boolean _hasVarData;

  public PDUDef ()
  {
    _pduName           = new String ();
    _field             = new ArrayList <PDUField> ( 0 );
    _sizeOfConstFields = 0;
    _hasVarData        = false;
  }
}

class TLVCodeGenData
{
  public ArrayList <PDUDef> _pdu;

  public TLVCodeGenData ()
  {
    _pdu = new ArrayList <PDUDef> ( 0 );
    // System.out.println ( "Size = " + _pdu.size () );
    // _pdu.add ( new PDUDef () );
    // System.out.println ( "Size = " + _pdu.size () );
  }
}

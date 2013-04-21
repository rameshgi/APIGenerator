import java.io.File;
import javax.xml.parsers.*;
import javax.xml.parsers.SAXParserFactory;
import org.xml.sax.*;
import org.xml.sax.helpers.DefaultHandler;
import java.lang.Boolean;

class TLVCodeGenXMLDefaultHandler extends DefaultHandler
{
  private TLVCodeGenData _xmlData;
  private int            _pduCount;

  private enum TagId { NAME, 
                       FIELD, 
		       POSITION, 
		       FIELD_NAME, 
		       TYPE, 
		       LENGTH,
		       MIN_LENGTH,
		       MAX_LENGTH,
		       DEF_VAL,
		       PDU_DEF };
  private TagId    _lastTag;
  private PDUField _currentPDUField;
  private PDUDef   _currentPDUDef;

  public TLVCodeGenXMLDefaultHandler ( TLVCodeGenData xmlData )
  {
    super ();
    _xmlData  = xmlData;
    _pduCount = -1;
    _lastTag   = TagId.NAME;
    _currentPDUField = new PDUField ();
    _currentPDUDef   = new PDUDef   ();
  }

  public void startElement ( String uri,
                             String localName,
			     String qName,
			     Attributes attributes )
  {
    // System.out.println ( qName.toString () );
    if      ( qName.equalsIgnoreCase ( "Name" ) )
    {
      _lastTag = TagId.NAME;
      ++_pduCount;
      _currentPDUDef   = new PDUDef ();
    }
    else if ( qName.equalsIgnoreCase ( "Field" ) )
    {
      // _currentPDUDef._field.add ( new PDUField () );
      _currentPDUField = new PDUField ();
      _lastTag = TagId.FIELD;
    }
    else if ( qName.equalsIgnoreCase ( "Position" ) )
    {
      _lastTag = TagId.POSITION;
    }
    else if ( qName.equalsIgnoreCase ( "FieldName" ) )
    {
      _lastTag = TagId.FIELD_NAME;
    }
    else if ( qName.equalsIgnoreCase ( "Type" ) )
    {
      _lastTag = TagId.TYPE;
    }
    else if ( qName.equalsIgnoreCase ( "Length" ) )
    {
      _lastTag = TagId.LENGTH;
    }
    else if ( qName.equalsIgnoreCase ( "MinLength" ) )
    {
      _lastTag = TagId.MIN_LENGTH;
    }
    else if ( qName.equalsIgnoreCase ( "MaxLength" ) )
    {
      _lastTag = TagId.MAX_LENGTH;
    }
    else if ( qName.equalsIgnoreCase ( "DefVal" ) )
    {
      _lastTag = TagId.DEF_VAL;
    }
    else if ( qName.equalsIgnoreCase ( "PDUDef" ) )
    {
      _lastTag = TagId.PDU_DEF;
    }
    else
    {
      // System.out.println ( "Tag not handled" );
    }
  }

  public void endElement ( String uri, 
                           String localName, 
			   String qName )
  {
    if      ( qName.equalsIgnoreCase ( "Field" ) )
    {
      _currentPDUDef._field.add ( _currentPDUField );
    }
    else if ( qName.equalsIgnoreCase ( "PDUDef" ) )
    {
      _xmlData._pdu.add ( _currentPDUDef );
      // printData ();
    }
  }

  public static void printData ( TLVCodeGenData xmlData )
  {
    if ( 0 < xmlData._pdu.size () )
    {
      for ( int pduDefIndex = 0;
                pduDefIndex < xmlData._pdu.size ();
		++pduDefIndex )
      {
        PDUDef pduDef = xmlData._pdu.get ( pduDefIndex );
	Boolean hasVar = new Boolean ( pduDef._hasVarData );
	System.out.println ( "PDU Name   : " + pduDef._pduName );
	System.out.println ( "Const Size : " + pduDef._sizeOfConstFields );
	System.out.println ( "Var Data   : " + hasVar.toString () );
	for ( int pduFieldIndex = 0;
	          pduFieldIndex < pduDef._field.size ();
		  ++pduFieldIndex )
        {
	  PDUField pduField = pduDef._field.get ( pduFieldIndex );
          System.out.println ( "    Position   : " + pduField._position );
          System.out.println ( "    Field Name : " + pduField._fieldName );
          System.out.println ( "    Type       : " + pduField._type );
          System.out.println ( "    Length     : " + pduField._length );

	  if ( true == pduField._hasMinLength )
	  {
            System.out.println ( "    Min Length : " 
	                                        + pduField._minLength );
	  }

	  if ( true == pduField._hasMaxLength )
	  {
            System.out.println ( "    Max Length : "
	                                        + pduField._maxLength );
	  }

	  if ( !pduField._defVal.isEmpty () )
	  {
            System.out.println ( "    Def Val    : " + pduField._defVal );
	  }

          System.out.println ( "------------------------------------" );
          System.out.println ( "------------------------------------" );
	}
      }
    }
  }

  public void characters ( char ch[], int start, int length )
  {
    // System.out.println ( "Charcters : Length = " + start + " " + length );
    // for ( int charCount = start;
    //          charCount <= ( start + length );
    //	      ++charCount )
    // {
    //   System.out.println ( ch [ charCount ] );
    // }
    String value = new String ( ch, start, length ).trim ();
    if ( !value.isEmpty () )
    {
      // System.out.println ( value );

      switch ( _lastTag )
      {
        case NAME:
	{
          _currentPDUDef._pduName = value;
	  break;
	}

	case FIELD:
	{
          // nothing;
	  break;
	}

	case POSITION:
	{
          _currentPDUField._position = value;
	  break;
	}

	case FIELD_NAME:
	{
          _currentPDUField._fieldName = value;
	  break;
	}

	case TYPE:
	{
          _currentPDUField._type = value;
	  break;
	}

	case LENGTH:
	{
          _currentPDUField._length = value;

	  if ( !value.equalsIgnoreCase ( "VAR" ) )
	  {
            _currentPDUDef._sizeOfConstFields = 
	                      _currentPDUDef._sizeOfConstFields + 
			      Integer.parseInt ( value );
	  }
	  else
	  {
            _currentPDUDef._hasVarData = true;
	  }
	  break;
	}

	case MIN_LENGTH:
	{
          _currentPDUField._minLength = value;
	  _currentPDUField._hasMinLength = true;
          break;
	}

	case MAX_LENGTH:
	{
          _currentPDUField._maxLength = value;
	  _currentPDUField._hasMaxLength = true;
	  break;
	}

	case DEF_VAL:
	{
          _currentPDUField._defVal = value;
	  break;
	}

	default:
	{

	}
      }
    }
  }
}

class TLVCodeGenXMLParser
{
  private String _xmlAbsFilePath;
  private TLVCodeGenData _parsedPDUData;

  public TLVCodeGenXMLParser ( TLVCodeGenData xmlData )
  {
    _xmlAbsFilePath = new String ();
    _parsedPDUData  = xmlData;
  }


  public void setAbsFilePath ( String filePath )
  {
    // _xmlAbsFilePath = filePath;
    _xmlAbsFilePath = new String ( "/home/ramesh/Tech/Projects/TLVCodeGen/TLVCodeGen.xml" );
  }

  public void parse ()
  {
    try
    {
      _xmlAbsFilePath = new String 
                 ( "/home/ramesh/Tech/Projects/TLVCodeGen/TLVCodeGen.xml" );
      File xmlFile = new File ( _xmlAbsFilePath );
      DefaultHandler parserHandler = new TLVCodeGenXMLDefaultHandler 
                                                     ( _parsedPDUData );
      SAXParser saxParser = SAXParserFactory.newInstance ().newSAXParser ();
      saxParser.parse ( xmlFile, parserHandler );
      // TLVCodeGenXMLDefaultHandler.printData ( _parsedPDUData );
    }

    catch (Exception e)
    {
      System.out.println ("Exception in parse " + e.toString () );
    }
  }

}

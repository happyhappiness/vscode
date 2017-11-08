static void
makeOS400IconvCode(char buf[ICONV_ID_SIZE], unsigned int ccsid)

{
  /**
  *** Convert a CCSID to the corresponding IBM iconv_open() character
  ***  code identifier.
  ***  This code is specific to the OS400 implementation of the iconv library.
  ***  CCSID 65535 (no conversion) is replaced by the ASCII CCSID.
  ***  CCSID 0 is interpreted by the OS400 as the job's CCSID.
  **/

  ccsid &= 0xFFFF;

  if(ccsid == NOCONV_CCSID)
    ccsid = ASCII_CCSID;

  memset(buf, 0, ICONV_ID_SIZE);
  curl_msprintf(buf, "IBMCCSID%05u0000000", ccsid);
}
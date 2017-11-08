static iconv_t
iconv_open_CCSID(unsigned int ccsidout, unsigned int ccsidin,
                                                        unsigned int cstr)

{
  char fromcode[ICONV_ID_SIZE];
  char tocode[ICONV_ID_SIZE];

  /**
  ***  Like iconv_open(), but character codes are given as CCSIDs.
  ***  If `cstr' is non-zero, conversion is set up to stop whenever a
  ***   null character is encountered.
  ***  See iconv_open() IBM description in "National Language Support API".
  **/

  makeOS400IconvCode(fromcode, ccsidin);
  makeOS400IconvCode(tocode, ccsidout);
  memset(tocode + 13, 0, sizeof tocode - 13);   /* Dest. code id format. */

  if(cstr)
    fromcode[18] = '1';                         /* Set null-terminator flag. */

  return iconv_open(tocode, fromcode);
}
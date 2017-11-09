static int
convert(char * d, size_t dlen, int dccsid,
        const char * s, int slen, int sccsid)

{
  int i;
  iconv_t cd;
  size_t lslen;

  /**
  ***  Convert `sccsid'-coded `slen'-data bytes at `s' into `dccsid'-coded
  ***   data stored in the `dlen'-byte buffer at `d'.
  ***  If `slen' < 0, source string is null-terminated.
  ***  CCSID 65535 (no conversion) is replaced by the ASCII CCSID.
  ***  Return the converted destination byte count, or -1 if error.
  **/

  if(sccsid == 65535)
    sccsid = ASCII_CCSID;

  if(dccsid == 65535)
    dccsid = ASCII_CCSID;

  if(sccsid == dccsid) {
    lslen = slen >= 0? slen: strlen(s) + 1;
    i = lslen < dlen? lslen: dlen;

    if(s != d && i > 0)
      memcpy(d, s, i);

    return i;
    }

  if(slen < 0) {
    lslen = 0;
    cd = iconv_open_CCSID(dccsid, sccsid, 1);
    }
  else {
    lslen = (size_t) slen;
    cd = iconv_open_CCSID(dccsid, sccsid, 0);
    }

  if(ICONV_OPEN_ERROR(cd))
    return -1;

  i = dlen;

  if((int) iconv(cd, (char * *) &s, &lslen, &d, &dlen) < 0)
    i = -1;
  else
    i -= dlen;

  iconv_close(cd);
  return i;
}
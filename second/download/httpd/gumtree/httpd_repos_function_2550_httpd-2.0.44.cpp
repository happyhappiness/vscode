static
void unknown_toUtf16(const ENCODING *enc,
		     const char **fromP, const char *fromLim,
		     unsigned short **toP, const unsigned short *toLim)
{
  while (*fromP != fromLim && *toP != toLim) {
    unsigned short c
      = ((const struct unknown_encoding *)enc)->utf16[(unsigned char)**fromP];
    if (c == 0) {
      c = (unsigned short)((const struct unknown_encoding *)enc)
	   ->convert(((const struct unknown_encoding *)enc)->userData, *fromP);
      *fromP += ((const struct normal_encoding *)enc)->type[(unsigned char)**fromP]
	         - (BT_LEAD2 - 2);
    }
    else
      (*fromP)++;
    *(*toP)++ = c;
  }
}
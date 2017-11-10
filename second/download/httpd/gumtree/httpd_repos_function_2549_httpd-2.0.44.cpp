static
void unknown_toUtf8(const ENCODING *enc,
		    const char **fromP, const char *fromLim,
		    char **toP, const char *toLim)
{
  char buf[XML_UTF8_ENCODE_MAX];
  for (;;) {
    const char *utf8;
    int n;
    if (*fromP == fromLim)
      break;
    utf8 = ((const struct unknown_encoding *)enc)->utf8[(unsigned char)**fromP];
    n = *utf8++;
    if (n == 0) {
      int c = ((const struct unknown_encoding *)enc)
	      ->convert(((const struct unknown_encoding *)enc)->userData, *fromP);
      n = XmlUtf8Encode(c, buf);
      if (n > toLim - *toP)
	break;
      utf8 = buf;
      *fromP += ((const struct normal_encoding *)enc)->type[(unsigned char)**fromP]
	         - (BT_LEAD2 - 2);
    }
    else {
      if (n > toLim - *toP)
	break;
      (*fromP)++;
    }
    do {
      *(*toP)++ = *utf8++;
    } while (--n != 0);
  }
}
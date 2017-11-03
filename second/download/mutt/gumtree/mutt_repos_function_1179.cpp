static size_t q_encoder (char *s, ICONV_CONST char *d, size_t dlen,
			 const char *tocode)
{
  static const char hex[] = "0123456789ABCDEF";
  char *s0 = s;

  memcpy (s, "=?", 2), s += 2;
  memcpy (s, tocode, strlen (tocode)), s += strlen (tocode);
  memcpy (s, "?Q?", 3), s += 3;
  while (dlen--)
  {
    unsigned char c = *d++;
    if (c == ' ')
      *s++ = '_';
    else if (c >= 0x7f || c < 0x20 || c == '_' ||  strchr (MimeSpecials, c))
    {
      *s++ = '=';
      *s++ = hex[(c & 0xf0) >> 4];
      *s++ = hex[c & 0x0f];
    }
    else
      *s++ = c;
  }
  memcpy (s, "?=", 2), s += 2;
  return s - s0;
}
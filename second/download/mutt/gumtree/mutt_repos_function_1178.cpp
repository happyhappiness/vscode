static size_t b_encoder (char *s, ICONV_CONST char *d, size_t dlen,
			 const char *tocode)
{
  char *s0 = s;

  memcpy (s, "=?", 2), s += 2;
  memcpy (s, tocode, strlen (tocode)), s += strlen (tocode);
  memcpy (s, "?B?", 3), s += 3;
  for (;;)
  {
    if (!dlen)
      break;
    else if (dlen == 1)
    {
      *s++ = B64Chars[(*d >> 2) & 0x3f];
      *s++ = B64Chars[(*d & 0x03) << 4];
      *s++ = '=';
      *s++ = '=';
      break;
    }
    else if (dlen == 2)
    {
      *s++ = B64Chars[(*d >> 2) & 0x3f];
      *s++ = B64Chars[((*d & 0x03) << 4) | ((d[1] >> 4) & 0x0f)];
      *s++ = B64Chars[(d[1] & 0x0f) << 2];
      *s++ = '=';
      break;
    }
    else
    {
      *s++ = B64Chars[(*d >> 2) & 0x3f];
      *s++ = B64Chars[((*d & 0x03) << 4) | ((d[1] >> 4) & 0x0f)];
      *s++ = B64Chars[((d[1] & 0x0f) << 2) | ((d[2] >> 6) & 0x03)];
      *s++ = B64Chars[d[2] & 0x3f];
      d += 3, dlen -= 3;
    }
  }
  memcpy (s, "?=", 2), s += 2;
  return s - s0;
}
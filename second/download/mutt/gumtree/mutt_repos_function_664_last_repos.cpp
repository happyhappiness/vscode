static int url_pct_decode (char *s)
{
  char *d;

  if (!s)
    return -1;

  for (d = s; *s; s++)
  {
    if (*s == '%')
    {
      if (s[1] && s[2] &&
	  isxdigit ((unsigned char) s[1]) &&
	  isxdigit ((unsigned char) s[2]) &&
	  hexval (s[1]) >= 0 && hexval (s[2]) >= 0)
      {
	*d++ = (hexval (s[1]) << 4) | (hexval (s[2]));
	s += 2;
      }
      else
	return -1;
    } else
      *d++ = *s;
  }
  *d ='\0';
  return 0;
}
static void url_pct_decode (char *s)
{
  char *d;

  if (!s)
    return;
  
  for (d = s; *s; s++)
  {
    if (*s == '%' && s[1] && s[2] &&
	hexval (s[1]) >= 0 && hexval(s[2]) >= 0)
    {
      *d++ = (hexval (s[1]) << 4) | (hexval (s[2]));
      s += 2;
    }
    else
      *d++ = *s;
  }
  *d ='\0';
}
static void rfc2231_decode_one (char *dest, char *src)
{
  char *d;

  for (d = dest; *src; src++)
  {
    if (*src == '%' && isxdigit (*(src + 1)) && isxdigit (*(src + 2)))
    {
      *d++ = (hexval (*(src + 1)) << 4) | (hexval (*(src + 2)));
      src += 2;
    }
    else
      *d++ = *src;
  }
  
  *d = '\0';
}
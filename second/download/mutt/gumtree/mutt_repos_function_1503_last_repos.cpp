static int
trim_incomplete_mbyte(unsigned char *buf, size_t len)
{
  mbstate_t mbstate;
  size_t k;

  memset (&mbstate, 0, sizeof (mbstate));
  for (; len > 0; buf += k, len -= k)
  {
    k = mbrtowc (NULL, (char *) buf, len, &mbstate);
    if (k == (size_t)(-2)) 
      break; 
    else if (k == (size_t)(-1) || k == 0)
    {
      if (k == (size_t)(-1))
        memset (&mbstate, 0, sizeof (mbstate));
      k = 1;
    }
  }
  *buf = '\0';

  return len;
}
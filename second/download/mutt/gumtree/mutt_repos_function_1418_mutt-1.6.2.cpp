static int
trim_incomplete_mbyte(unsigned char *buf, size_t len)
{
  mbstate_t mbstate;
  size_t k;

  memset (&mbstate, 0, sizeof (mbstate));
  for (; len > 0; buf += k, len -= k)
  {
    k = mbrtowc (NULL, (char *) buf, len, &mbstate);
    if (k == -2) 
      break; 
    else if (k == -1 || k == 0) 
      k = 1;
  }
  *buf = '\0';

  return len;
}
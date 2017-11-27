static lt_ptr
memmove (dest, src, size)
     lt_ptr dest;
     const lt_ptr src;
     size_t size;
{
  const char *	s = src;
  char *	d = dest;
  size_t	i;

  if (d < s)
    for (i = 0; i < size; ++i)
      {
	d[i] = s[i];
      }
  else if (d > s && size > 0)
    for (i = size -1; ; --i)
      {
	d[i] = s[i];
	if (i == 0)
	  break;
      }

  return dest;
}
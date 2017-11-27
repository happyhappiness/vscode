static lt_ptr
memcpy (dest, src, size)
     lt_ptr dest;
     const lt_ptr src;
     size_t size;
{
  const char *	s = src;
  char *	d = dest;
  size_t	i = 0;

  for (i = 0; i < size; ++i)
    {
      d[i] = s[i];
    }

  return dest;
}
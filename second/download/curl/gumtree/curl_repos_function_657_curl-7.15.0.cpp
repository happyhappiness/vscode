static size_t
strlcpy (char *dst, const char *src, size_t dst_sz)
{
  size_t n;
  char *p;

  for (p = dst, n = 0;
       n + 1 < dst_sz && *src != '\0';
       ++p, ++src, ++n)
    *p = *src;
  *p = '\0';
  if (*src == '\0')
    return n;
  else
    return n + strlen (src);
}
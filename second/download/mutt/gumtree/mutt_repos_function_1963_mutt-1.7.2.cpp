static int
longest_common_prefix (char *dest, const char* src, int start, size_t dlen)
{
  int pos = start;

  while (pos < dlen && dest[pos] && dest[pos] == src[pos])
    pos++;
  dest[pos] = '\0';

  return pos;
}
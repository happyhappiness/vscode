static void dopr_outch (char *buffer, size_t *currlen, size_t maxlen, char c)
{
  if (*currlen < maxlen)
    buffer[*currlen] = c;
  (*currlen)++;
}
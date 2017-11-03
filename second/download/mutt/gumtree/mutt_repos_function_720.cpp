static int line_compare(const char *a, size_t n, const char *b)
{
  if (mutt_strncmp(a, b, n) == 0)
  {
    /* at this point we know that 'b' is at least 'n' chars long */
    if (b[n] == '\n' || (b[n] == '\r' && b[n+1] == '\n'))
      return 0;
  }
  return -1;
}
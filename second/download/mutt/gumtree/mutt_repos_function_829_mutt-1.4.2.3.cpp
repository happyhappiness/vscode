int mutt_needs_quote (const char *s)
{
  while (*s)
  {
    if (INVALID_CHAR (*s))
      return 1;
    s++;
  }
  return 0;
}
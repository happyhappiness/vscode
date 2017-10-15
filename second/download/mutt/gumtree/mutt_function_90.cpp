static int print_val (FILE *fp, const char *pfx, const char *value,
		      int flags, size_t col)
{
  while (value && *value)
  {
    if (fputc (*value, fp) == EOF)
      return -1;
    /* corner-case: break words longer than 998 chars by force,
     * mandated by RfC5322 */
    if (!(flags & CH_DISPLAY) && ++col >= 998)
    {
      if (fputs ("\n ", fp) < 0)
	return -1;
      col = 1;
    }
    if (*value == '\n')
    {
      if (*(value + 1) && pfx && *pfx && fputs (pfx, fp) == EOF)
	return -1;
      /* for display, turn folding spaces into folding tabs */
      if ((flags & CH_DISPLAY) && (*(value + 1) == ' ' || *(value + 1) == '\t'))
      {
	value++;
	while (*value && (*value == ' ' || *value == '\t'))
	  value++;
	if (fputc ('\t', fp) == EOF)
	  return -1;
	continue;
      }
    }
    value++;
  }
  return 0;
}
int safe_asprintf (char **strp, const char *fmt, ...)
{
  int rlen = STRING;
  int n;

  *strp = safe_malloc (rlen);
  for (;;)
  {
    va_list ap;
    va_start (ap, fmt);
    n = vsnprintf (*strp, rlen, fmt, ap);
    va_end (ap);
    if (n < 0)
    {
      FREE (strp); /* __FREE_CHECKED__ */
      return n;
    }

    if (n < rlen)
    {
      /* reduce space to just that which was used.  note that 'n' does not
       * include the terminal nul char.
       */
      if (n == 0) /* convention is to use NULL for zero-length strings. */
	FREE (strp); /* __FREE_CHECKED__ */
      else if (n != rlen - 1)
	safe_realloc (strp, n + 1);
      return n;
    }
    /* increase size and try again */
    rlen = n + 1;
    safe_realloc (strp, rlen);
  }
  /* not reached */
}
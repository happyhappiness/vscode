static int match_adrlist (regex_t *rx, int match_personal, int alladdr,
			  int n, ...)
{
  va_list ap;
  ADDRESS *a;

  va_start (ap, n);
  for ( ; n ; n --)
  {
    for (a = va_arg (ap, ADDRESS *) ; a ; a = a->next)
    {
      if (alladdr^
	  ((a->mailbox && regexec (rx, a->mailbox, 0, NULL, 0) == 0) ||
	   (match_personal && a->personal &&
	    regexec (rx, a->personal, 0, NULL, 0) == 0)))
      {
	va_end (ap);
	return (! alladdr); /* Found match, or non-match if alladdr */
      }
    }
  }
  va_end (ap);
  return alladdr; /* No matches, or all matches if alladdr */
}
static int match_adrlist (pattern_t *pat, int match_personal, int n, ...)
{
  va_list ap;
  ADDRESS *a;

  va_start (ap, n);
  for ( ; n ; n --)
  {
    for (a = va_arg (ap, ADDRESS *) ; a ; a = a->next)
    {
      if (pat->alladdr ^ ((a->mailbox && patmatch (pat, a->mailbox) == 0) ||
	   (match_personal && a->personal && patmatch (pat, a->personal) == 0)))
      {
	va_end (ap);
	return (! pat->alladdr); /* Found match, or non-match if alladdr */
      }
    }
  }
  va_end (ap);
  return pat->alladdr; /* No matches, or all matches if alladdr */
}
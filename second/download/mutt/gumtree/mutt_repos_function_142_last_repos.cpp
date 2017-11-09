static int match_adrlist (pattern_t *pat, int match_personal, int n, ...)
{
  va_list ap;
  ADDRESS *a;

  va_start (ap, n);
  for ( ; n ; n --)
  {
    for (a = va_arg (ap, ADDRESS *) ; a ; a = a->next)
    {
      if (pat->alladdr ^
          ((!pat->isalias || alias_reverse_lookup (a)) &&
           ((a->mailbox && !patmatch (pat, a->mailbox)) ||
	    (match_personal && a->personal && !patmatch (pat, a->personal) ))))
      {
	va_end (ap);
	return (! pat->alladdr); /* Found match, or non-match if alladdr */
      }
    }
  }
  va_end (ap);
  return pat->alladdr; /* No matches, or all matches if alladdr */
}
ADDRESS *mutt_parse_adrlist (ADDRESS *p, const char *s)
{
  const char *q;

  /* check for a simple whitespace separated list of addresses */
  if ((q = strpbrk (s, "\"<>():;,\\")) == NULL)
  {
    char tmp[HUGE_STRING];
    char *r;

    strfcpy (tmp, s, sizeof (tmp));
    r = tmp;
    while ((r = strtok (r, " \t")) != NULL)
    {
      p = rfc822_parse_adrlist (p, r);
      r = NULL;
    }
  }
  else
    p = rfc822_parse_adrlist (p, s);
  
  return p;
}
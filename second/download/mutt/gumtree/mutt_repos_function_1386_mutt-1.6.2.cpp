REGEXP *mutt_compile_regexp (const char *s, int flags)
{
  REGEXP *pp = safe_calloc (sizeof (REGEXP), 1);
  pp->pattern = safe_strdup (s);
  pp->rx = safe_calloc (sizeof (regex_t), 1);
  if (REGCOMP (pp->rx, NONULL(s), flags) != 0)
    mutt_free_regexp (&pp);

  return pp;
}
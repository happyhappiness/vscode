ADDRESS *mutt_lookup_alias (const char *s)
{
  ALIAS *t = Aliases;

  for (; t; t = t->next)
    if (!mutt_strcasecmp (s, t->name))
      return (t->addr);
  return (NULL);   /* no such alias */
}
group_t *mutt_pattern_group (const char *k)
{
  group_t *p;

  if (!k)
    return 0;

  if (!(p = hash_find (Groups, k)))
  {
    dprint (2, (debugfile, "mutt_pattern_group: Creating group %s.\n", k));
    p = safe_calloc (1, sizeof (group_t));
    p->name = safe_strdup (k);
    hash_insert (Groups, p->name, p, 0);
  }

  return p;
}
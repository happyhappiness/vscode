ADDRESS *mutt_expand_aliases (ADDRESS *a)
{
  ADDRESS *t;
  LIST *expn = NULL; /* previously expanded aliases to avoid loops */

  t = mutt_expand_aliases_r (a, &expn);
  mutt_free_list (&expn);
  return (mutt_remove_duplicates (t));
}
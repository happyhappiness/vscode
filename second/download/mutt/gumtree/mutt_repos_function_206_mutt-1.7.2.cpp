void mutt_group_add_adrlist (group_t *g, ADDRESS *a)
{
  ADDRESS **p, *q;

  if (!g)
    return;
  if (!a)
    return;

  for (p = &g->as; *p; p = &((*p)->next))
    ;

  q = rfc822_cpy_adr (a, 0);
  q = mutt_remove_xrefs (g->as, q);
  *p = q;
}
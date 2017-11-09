static int mutt_group_remove_adrlist (group_t *g, ADDRESS *a)
{
  ADDRESS *p;

  if (!g)
    return -1;
  if (!a)
    return -1;

  for (p = a; p; p = p->next)
    rfc822_remove_from_adrlist (&g->as, p->mailbox);

  return 0;
}
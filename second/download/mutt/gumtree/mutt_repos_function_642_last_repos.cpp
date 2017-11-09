void mutt_alias_delete_reverse (ALIAS *t)
{
  ADDRESS *ap;
  if (!t)
    return;

  /* If the alias addresses were converted to local form, they won't
   * match the hash entries. */
  mutt_addrlist_to_intl (t->addr, NULL);

  for (ap = t->addr; ap; ap = ap->next)
  {
    if (!ap->group && ap->mailbox)
      hash_delete (ReverseAlias, ap->mailbox, ap, NULL);
  }
}
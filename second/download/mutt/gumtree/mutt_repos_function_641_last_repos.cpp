void mutt_alias_add_reverse (ALIAS *t)
{
  ADDRESS *ap;
  if (!t)
    return;

  /* Note that the address mailbox should be converted to intl form
   * before using as a key in the hash.  This is currently done
   * by all callers, but added here mostly as documentation.. */
  mutt_addrlist_to_intl (t->addr, NULL);

  for (ap = t->addr; ap; ap = ap->next)
  {
    if (!ap->group && ap->mailbox)
      hash_insert (ReverseAlias, ap->mailbox, ap);
  }
}
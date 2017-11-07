void mutt_alias_add_reverse (ALIAS *t)
{
  ADDRESS *ap;
  if (!t)
    return;
  
  for (ap = t->addr; ap; ap = ap->next)
  {
    if (!ap->group && ap->mailbox)
      hash_insert (ReverseAlias, ap->mailbox, ap, 1);
  }
}
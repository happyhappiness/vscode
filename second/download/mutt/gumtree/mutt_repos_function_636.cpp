void mutt_alias_delete_reverse (ALIAS *t)
{
  ADDRESS *ap;
  if (!t)
    return;
  
  for (ap = t->addr; ap; ap = ap->next)
  {
    if (!ap->group && ap->mailbox)
      hash_delete (ReverseAlias, ap->mailbox, ap, NULL);
  }
}
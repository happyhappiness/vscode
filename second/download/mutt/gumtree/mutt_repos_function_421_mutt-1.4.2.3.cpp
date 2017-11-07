ADDRESS *alias_reverse_lookup (ADDRESS *a)
{
  ALIAS *t = Aliases;
  ADDRESS *ap;

  if (!a || !a->mailbox)
    return NULL;

  for (; t; t = t->next)
  {
    /* cycle through all addresses if this is a group alias */
    for (ap = t->addr; ap; ap = ap->next)
    {
      if (!ap->group && ap->mailbox &&
	  ascii_strcasecmp (ap->mailbox, a->mailbox) == 0)
	return ap;
    }
  }
  return 0;
}
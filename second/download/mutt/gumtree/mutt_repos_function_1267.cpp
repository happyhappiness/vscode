ADDRESS *mutt_remove_duplicates (ADDRESS *addr)
{
  ADDRESS *top = addr;
  ADDRESS **last = &top;
  ADDRESS *tmp;
  int dup;

  while (addr)
  {
    for (tmp = top, dup = 0; tmp && tmp != addr; tmp = tmp->next)
    {
      if (tmp->mailbox && addr->mailbox &&
	  !ascii_strcasecmp (addr->mailbox, tmp->mailbox))
      {
	dup = 1;
	break;
      }
    }

    if (dup)
    {
      dprint (2, (debugfile, "mutt_remove_duplicates: Removing %s\n",
		  addr->mailbox));

      *last = addr->next;

      addr->next = NULL;
      rfc822_free_address(&addr);

      addr = *last;
    }
    else
    {
      last = &addr->next;
      addr = addr->next;
    }
  }

  return (top);
}
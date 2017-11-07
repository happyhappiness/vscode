ADDRESS *mutt_remove_duplicates (ADDRESS *addr)
{
  ADDRESS *top = NULL;
  ADDRESS *tmp;
  
  if ((top = addr) == NULL)
    return (NULL);
  addr = addr->next;
  top->next = NULL;
  while (addr)
  {
    tmp = top;
    do {
      if (addr->mailbox && tmp->mailbox &&
	  !ascii_strcasecmp (addr->mailbox, tmp->mailbox))
      {
	/* duplicate address, just ignore it */
	tmp = addr;
	addr = addr->next;
	tmp->next = NULL;
	rfc822_free_address (&tmp);
      }
      else if (!tmp->next)
      {
	/* unique address.  add it to the list */
	tmp->next = addr;
	addr = addr->next;
	tmp = tmp->next;
	tmp->next = NULL;
	tmp = NULL; /* so we exit the loop */
      }
      else
	tmp = tmp->next;
    } while (tmp);
  }

  return (top);
}
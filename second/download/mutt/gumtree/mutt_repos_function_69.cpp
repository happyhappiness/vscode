ADDRESS *mutt_remove_xrefs (ADDRESS *a, ADDRESS *b)
{
  ADDRESS *top, *p, *prev = NULL;

  top = b;
  while (b)
  {
    for (p = a; p; p = p->next)
    {
      if (mutt_addrcmp (p, b))
	break;
    }
    if (p)
    {
      if (prev)
      {
	prev->next = b->next;
	b->next = NULL;
	rfc822_free_address (&b);
	b = prev;
      }
      else
      {
	top = top->next;
	b->next = NULL;
	rfc822_free_address (&b);
	b = top;
      }
    }
    else
    {
      prev = b;
      b = b->next;
    }
  }
  return top;
}
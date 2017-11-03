static ADDRESS *remove_user (ADDRESS *a, int leave_only)
{
  ADDRESS *top = NULL, *last = NULL;

  while (a)
  {
    if (!mutt_addr_is_user (a))
    {
      if (top)
      {
        last->next = a;
        last = last->next;
      }
      else
        last = top = a;
      a = a->next;
      last->next = NULL;
    }
    else
    {
      ADDRESS *tmp = a;
      
      a = a->next;
      if (!leave_only || a || last)
      {
	tmp->next = NULL;
	rfc822_free_address (&tmp);
      }
      else
	last = top = tmp;
    }
  }
  return top;
}
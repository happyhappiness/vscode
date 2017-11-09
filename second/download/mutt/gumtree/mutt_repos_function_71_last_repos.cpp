static ADDRESS *find_mailing_lists (ADDRESS *t, ADDRESS *c)
{
  ADDRESS *top = NULL, *ptr = NULL;

  for (; t || c; t = c, c = NULL)
  {
    for (; t; t = t->next)
    {
      if (mutt_is_mail_list (t) && !t->group)
      {
	if (top)
	{
	  ptr->next = rfc822_cpy_adr_real (t);
	  ptr = ptr->next;
	}
	else
	  ptr = top = rfc822_cpy_adr_real (t);
      }
    }
  }
  return top;
}
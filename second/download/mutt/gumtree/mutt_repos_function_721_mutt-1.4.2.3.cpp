static int _mutt_is_mail_list (ADDRESS *addr, LIST *p)
{
  if (addr->mailbox)
  {
    for (;p; p = p->next)
      if (mutt_strncasecmp (addr->mailbox, p->data, mutt_strlen (p->data)) == 0)
	return 1;
  }
  return 0;
}
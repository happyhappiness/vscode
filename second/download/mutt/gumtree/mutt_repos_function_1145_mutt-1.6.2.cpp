static int
check_for_mailing_list_addr (ADDRESS *adr, char *buf, int buflen)
{
  for (; adr; adr = adr->next)
  {
    if (mutt_is_subscribed_list (adr))
    {
      if (buf && buflen)
	snprintf (buf, buflen, "%s", adr->mailbox);
      return 1;
    }
  }
  return 0;
}
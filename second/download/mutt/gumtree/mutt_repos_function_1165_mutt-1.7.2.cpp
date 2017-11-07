static int
check_for_mailing_list (ADDRESS *adr, char *pfx, char *buf, int buflen)
{
  for (; adr; adr = adr->next)
  {
    if (mutt_is_subscribed_list (adr))
    {
      if (pfx && buf && buflen)
	snprintf (buf, buflen, "%s%s", pfx, mutt_get_name (adr));
      return 1;
    }
  }
  return 0;
}
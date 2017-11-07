const char *mutt_addr_for_display (ADDRESS *a)
{
  char *user = NULL, *domain = NULL;
  static char *buff = NULL;
  char *local_mailbox = NULL;

  FREE (&buff);

  if (!a->mailbox || addr_is_local (a))
    return a->mailbox;

  if (mbox_to_udomain (a->mailbox, &user, &domain) == -1)
    return a->mailbox;

  local_mailbox = intl_to_local (user, domain, MI_MAY_BE_IRREVERSIBLE);
  if (! local_mailbox)
    return a->mailbox;

  mutt_str_replace (&buff, local_mailbox);
  FREE (&local_mailbox);
  return buff;
}
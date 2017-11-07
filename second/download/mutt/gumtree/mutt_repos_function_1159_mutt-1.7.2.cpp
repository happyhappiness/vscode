int mutt_addrlist_to_local (ADDRESS *a)
{
  char *user = NULL, *domain = NULL;
  char *local_mailbox = NULL;

  for (; a; a = a->next)
  {
    if (!a->mailbox || addr_is_local (a))
      continue;

    if (mbox_to_udomain (a->mailbox, &user, &domain) == -1)
      continue;

    local_mailbox = intl_to_local (user, domain, 0);
    if (local_mailbox)
      set_local_mailbox (a, local_mailbox);
  }

  return 0;
}
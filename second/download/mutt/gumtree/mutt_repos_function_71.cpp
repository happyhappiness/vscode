int mutt_addrlist_to_intl (ADDRESS *a, char **err)
{
  char *user = NULL, *domain = NULL;
  char *intl_mailbox = NULL;
  int rv = 0;

  if (err)
    *err = NULL;

  for (; a; a = a->next)
  {
    if (!a->mailbox || addr_is_intl (a))
      continue;

    if (mbox_to_udomain (a->mailbox, &user, &domain) == -1)
      continue;

    intl_mailbox = local_to_intl (user, domain);
    if (! intl_mailbox)
    {
      rv = -1;
      if (err && !*err)
        *err = safe_strdup (a->mailbox);
      continue;
    }

    set_intl_mailbox (a, intl_mailbox);
  }

  return rv;
}
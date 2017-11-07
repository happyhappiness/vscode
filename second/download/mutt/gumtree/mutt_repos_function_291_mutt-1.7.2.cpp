int mutt_account_match (const ACCOUNT* a1, const ACCOUNT* a2)
{
  const char* user = NONULL (Username);

  if (a1->type != a2->type)
    return 0;
  if (ascii_strcasecmp (a1->host, a2->host))
    return 0;
  if (a1->port != a2->port)
    return 0;

#ifdef USE_IMAP
  if (a1->type == MUTT_ACCT_TYPE_IMAP)
  {
    if (ImapUser)
      user = ImapUser;
  }
#endif

#ifdef USE_POP
  if (a1->type == MUTT_ACCT_TYPE_POP && PopUser)
    user = PopUser;
#endif
  
  if (a1->flags & a2->flags & MUTT_ACCT_USER)
    return (!strcmp (a1->user, a2->user));
  if (a1->flags & MUTT_ACCT_USER)
    return (!strcmp (a1->user, user));
  if (a2->flags & MUTT_ACCT_USER)
    return (!strcmp (a2->user, user));

  return 1;
}
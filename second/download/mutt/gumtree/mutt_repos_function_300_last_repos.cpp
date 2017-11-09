int mutt_account_getlogin (ACCOUNT* account)
{
  /* already set */
  if (account->flags & MUTT_ACCT_LOGIN)
    return 0;
#ifdef USE_IMAP
  else if (account->type == MUTT_ACCT_TYPE_IMAP)
  {
    if (ImapLogin)
    {
      strfcpy (account->login, ImapLogin, sizeof (account->login));
      account->flags |= MUTT_ACCT_LOGIN;
    }
  }
#endif

  if (!(account->flags & MUTT_ACCT_LOGIN))
  {
    mutt_account_getuser (account);
    strfcpy (account->login, account->user, sizeof (account->login));
  }

  account->flags |= MUTT_ACCT_LOGIN;

  return 0;
}
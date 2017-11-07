int mutt_account_getpass (ACCOUNT* account)
{
  char prompt[SHORT_STRING];

  if (account->flags & M_ACCT_PASS)
    return 0;
#ifdef USE_IMAP
  else if ((account->type == M_ACCT_TYPE_IMAP) && ImapPass)
    strfcpy (account->pass, ImapPass, sizeof (account->pass));
#endif
#ifdef USE_POP
  else if ((account->type == M_ACCT_TYPE_POP) && PopPass)
    strfcpy (account->pass, PopPass, sizeof (account->pass));
#endif
  else
  {
    snprintf (prompt, sizeof (prompt), _("Password for %s@%s: "),
      account->user, account->host);
    account->pass[0] = '\0';
    if (mutt_get_field (prompt, account->pass, sizeof (account->pass), M_PASS))
      return -1;
  }

  account->flags |= M_ACCT_PASS;

  return 0;
}
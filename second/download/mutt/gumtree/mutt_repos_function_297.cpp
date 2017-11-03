void mutt_account_unsetpass (ACCOUNT* account)
{
  account->flags &= ~MUTT_ACCT_PASS;
}
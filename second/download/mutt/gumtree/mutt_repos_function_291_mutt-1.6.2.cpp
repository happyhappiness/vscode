void mutt_account_unsetpass (ACCOUNT* account)
{
  account->flags &= ~M_ACCT_PASS;
}
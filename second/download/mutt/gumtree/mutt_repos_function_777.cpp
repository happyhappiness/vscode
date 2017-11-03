static int mutt_sasl_cb_authname (void* context, int id, const char** result,
  unsigned* len)
{
  ACCOUNT* account = (ACCOUNT*) context;

  if (!result)
    return SASL_FAIL;

  *result = NULL;
  if (len)
    *len = 0;

  if (!account)
    return SASL_BADPARAM;

  dprint (2, (debugfile, "mutt_sasl_cb_authname: getting %s for %s:%u\n",
	      id == SASL_CB_AUTHNAME ? "authname" : "user",
	      account->host, account->port));

  if (id == SASL_CB_AUTHNAME)
  {
    if (mutt_account_getlogin (account))
      return SASL_FAIL;
    *result = account->login;
  }
  else
  {
    if (mutt_account_getuser (account))
      return SASL_FAIL;
    *result = account->user;
  }
  
  if (len)
    *len = strlen (*result);

  return SASL_OK;
}
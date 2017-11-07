static int mutt_sasl_cb_pass (sasl_conn_t* conn, void* context, int id,
  sasl_secret_t** psecret)
{
  ACCOUNT* account = (ACCOUNT*) context;
  int len;

  if (!account || !psecret)
    return SASL_BADPARAM;

  dprint (2, (debugfile,
    "mutt_sasl_cb_pass: getting password for %s@%s:%u\n", account->login,
    account->host, account->port));

  if (mutt_account_getpass (account))
    return SASL_FAIL;

  len = strlen (account->pass);

  *psecret = (sasl_secret_t*) safe_malloc (sizeof (sasl_secret_t) + len);
  (*psecret)->len = len;
  strcpy ((char*)(*psecret)->data, account->pass);	/* __STRCPY_CHECKED__ */

  return SASL_OK;
}
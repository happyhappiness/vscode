static int ssl_passwd_cb(char *buf, int size, int rwflag, void *userdata)
{
  ACCOUNT *account = (ACCOUNT*)userdata;

  if (mutt_account_getuser (account))
    return 0;

  dprint (2, (debugfile, "ssl_passwd_cb: getting password for %s@%s:%u\n",
	      account->user, account->host, account->port));

  if (mutt_account_getpass (account))
    return 0;

  return snprintf(buf, size, "%s", account->pass);
}
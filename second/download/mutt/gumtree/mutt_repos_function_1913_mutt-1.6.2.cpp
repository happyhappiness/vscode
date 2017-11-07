imap_auth_res_t imap_auth_login (IMAP_DATA* idata, const char* method)
{
  char q_user[SHORT_STRING], q_pass[SHORT_STRING];
  char buf[STRING];
  int rc;

  if (mutt_bit_isset (idata->capabilities, LOGINDISABLED))
  {
    mutt_message _("LOGIN disabled on this server.");
    return IMAP_AUTH_UNAVAIL;
  }

  if (mutt_account_getuser (&idata->conn->account))
    return IMAP_AUTH_FAILURE;
  if (mutt_account_getpass (&idata->conn->account))
    return IMAP_AUTH_FAILURE;

  mutt_message _("Logging in...");

  imap_quote_string (q_user, sizeof (q_user), idata->conn->account.user);
  imap_quote_string (q_pass, sizeof (q_pass), idata->conn->account.pass);

#ifdef DEBUG
  /* don't print the password unless we're at the ungodly debugging level
   * of 5 or higher */

  if (debuglevel < IMAP_LOG_PASS)
    dprint (2, (debugfile, "Sending LOGIN command for %s...\n",
      idata->conn->account.user));
#endif

  snprintf (buf, sizeof (buf), "LOGIN %s %s", q_user, q_pass);
  rc = imap_exec (idata, buf, IMAP_CMD_FAIL_OK | IMAP_CMD_PASS);
  
  if (!rc)
  {
    mutt_clear_error(); /* clear "Logging in...".  fixes #3524 */
    return IMAP_AUTH_SUCCESS;
  }

  mutt_error _("Login failed.");
  mutt_sleep (2);
  return IMAP_AUTH_FAILURE;
}
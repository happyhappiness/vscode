static int smtp_auth (CONNECTION* conn)
{
  int r = SMTP_AUTH_UNAVAIL;

  if (SmtpAuthenticators && *SmtpAuthenticators)
  {
    char* methods = safe_strdup (SmtpAuthenticators);
    char* method;
    char* delim;

    for (method = methods; method; method = delim)
    {
      delim = strchr (method, ':');
      if (delim)
	*delim++ = '\0';
      if (! method[0])
	continue;

      dprint (2, (debugfile, "smtp_authenticate: Trying method %s\n", method));

      r = smtp_auth_sasl (conn, method);
      
      if (r == SMTP_AUTH_FAIL && delim)
      {
        mutt_error (_("%s authentication failed, trying next method"), method);
        mutt_sleep (1);
      }
      else if (r != SMTP_AUTH_UNAVAIL)
        break;
    }

    FREE (&methods);
  }
  else
    r = smtp_auth_sasl (conn, AuthMechs);

  if (r != SMTP_AUTH_SUCCESS)
    mutt_account_unsetpass (&conn->account);

  if (r == SMTP_AUTH_FAIL)
  {
    mutt_error (_("SASL authentication failed"));
    mutt_sleep (1);
  }
  else if (r == SMTP_AUTH_UNAVAIL)
  {
    mutt_error (_("No authenticators available"));
    mutt_sleep (1);
  }

  return r == SMTP_AUTH_SUCCESS ? 0 : -1;
}
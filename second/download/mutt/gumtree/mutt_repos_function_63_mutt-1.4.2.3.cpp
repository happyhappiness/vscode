static pop_auth_res_t pop_auth_apop (POP_DATA *pop_data, const char *method)
{
  MD5_CTX mdContext;
  unsigned char digest[16];
  char hash[33];
  char buf[LONG_STRING];
  int i;

  if (!pop_data->timestamp)
    return POP_A_UNAVAIL;

  if (rfc822_valid_msgid (pop_data->timestamp) < 0)
  {
    mutt_error _("POP timestamp is invalid!");
    mutt_sleep (2);
    return POP_A_UNAVAIL;
  }

  mutt_message _("Authenticating (APOP)...");

  /* Compute the authentication hash to send to the server */
  MD5Init (&mdContext);
  MD5Update (&mdContext, (unsigned char *)pop_data->timestamp,
	     strlen (pop_data->timestamp));
  MD5Update (&mdContext, (unsigned char *)pop_data->conn->account.pass,
	     strlen (pop_data->conn->account.pass));
  MD5Final (digest, &mdContext);

  for (i = 0; i < sizeof (digest); i++)
    sprintf (hash + 2 * i, "%02x", digest[i]);

  /* Send APOP command to server */
  snprintf (buf, sizeof (buf), "APOP %s %s\r\n", pop_data->conn->account.user, hash);

  switch (pop_query (pop_data, buf, sizeof (buf)))
  {
    case 0:
      return POP_A_SUCCESS;
    case -1:
      return POP_A_SOCKET;
  }

  mutt_error _("APOP authentication failed.");
  mutt_sleep (2);

  return POP_A_FAILURE;
}
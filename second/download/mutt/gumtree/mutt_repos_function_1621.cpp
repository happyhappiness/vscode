static int smtp_auth_sasl (CONNECTION* conn, const char* mechlist)
{
  sasl_conn_t* saslconn;
  sasl_interact_t* interaction = NULL;
  const char* mech;
  const char* data = NULL;
  unsigned int len;
  char *buf = NULL;
  size_t bufsize = 0;
  int rc, saslrc;

  if (mutt_sasl_client_new (conn, &saslconn) < 0)
    return SMTP_AUTH_FAIL;

  do
  {
    rc = sasl_client_start (saslconn, mechlist, &interaction, &data, &len, &mech);
    if (rc == SASL_INTERACT)
      mutt_sasl_interact (interaction);
  }
  while (rc == SASL_INTERACT);

  if (rc != SASL_OK && rc != SASL_CONTINUE)
  {
    dprint (2, (debugfile, "smtp_auth_sasl: %s unavailable\n", mech));
    sasl_dispose (&saslconn);
    return SMTP_AUTH_UNAVAIL;
  }

  if (!option(OPTNOCURSES))
    mutt_message (_("Authenticating (%s)..."), mech);

  bufsize = ((len * 2) > LONG_STRING) ? (len * 2) : LONG_STRING;
  buf = safe_malloc (bufsize);

  snprintf (buf, bufsize, "AUTH %s", mech);
  if (len)
  {
    safe_strcat (buf, bufsize, " ");
    if (sasl_encode64 (data, len, buf + mutt_strlen (buf),
                       bufsize - mutt_strlen (buf), &len) != SASL_OK)
    {
      dprint (1, (debugfile, "smtp_auth_sasl: error base64-encoding client response.\n"));
      goto fail;
    }
  }
  safe_strcat (buf, bufsize, "\r\n");

  do {
    if (mutt_socket_write (conn, buf) < 0)
      goto fail;
    if ((rc = mutt_socket_readln (buf, bufsize, conn)) < 0)
      goto fail;
    if (smtp_code (buf, rc, &rc) < 0)
      goto fail;

    if (rc != smtp_ready)
      break;

    if (sasl_decode64 (buf+4, strlen (buf+4), buf, bufsize - 1, &len) != SASL_OK)
    {
      dprint (1, (debugfile, "smtp_auth_sasl: error base64-decoding server response.\n"));
      goto fail;
    }

    do
    {
      saslrc = sasl_client_step (saslconn, buf, len, &interaction, &data, &len);
      if (saslrc == SASL_INTERACT)
        mutt_sasl_interact (interaction);
    }
    while (saslrc == SASL_INTERACT);

    if (len)
    {
      if ((len * 2) > bufsize)
      {
        bufsize = len * 2;
        safe_realloc (&buf, bufsize);
      }
      if (sasl_encode64 (data, len, buf, bufsize, &len) != SASL_OK)
      {
        dprint (1, (debugfile, "smtp_auth_sasl: error base64-encoding client response.\n"));
        goto fail;
      }
    }
    strfcpy (buf + len, "\r\n", bufsize - len);
  } while (rc == smtp_ready && saslrc != SASL_FAIL);

  if (smtp_success (rc))
  {
    mutt_sasl_setup_conn (conn, saslconn);
    FREE (&buf);
    return SMTP_AUTH_SUCCESS;
  }

fail:
  sasl_dispose (&saslconn);
  FREE (&buf);
  return SMTP_AUTH_FAIL;
}
static pop_auth_res_t pop_auth_sasl (POP_DATA *pop_data, const char *method)
{
  sasl_conn_t *saslconn;
  sasl_interact_t *interaction = NULL;
  int rc;
  char *buf = NULL;
  size_t bufsize = 0;
  char inbuf[LONG_STRING];
  const char* mech;
  const char *pc = NULL;
  unsigned int len, olen, client_start;

  if (mutt_sasl_client_new (pop_data->conn, &saslconn) < 0)
  {
    dprint (1, (debugfile, "pop_auth_sasl: Error allocating SASL connection.\n"));
    return POP_A_FAILURE;
  }

  if (!method)
    method = pop_data->auth_list;

  FOREVER
  {
    rc = sasl_client_start(saslconn, method, &interaction, &pc, &olen, &mech);
    if (rc != SASL_INTERACT)
      break;
    mutt_sasl_interact (interaction);
  }

  if (rc != SASL_OK && rc != SASL_CONTINUE)
  {
    dprint (1, (debugfile, "pop_auth_sasl: Failure starting authentication exchange. No shared mechanisms?\n"));

    /* SASL doesn't support suggested mechanisms, so fall back */
    return POP_A_UNAVAIL;
  }

  /* About client_start:  If sasl_client_start() returns data via pc/olen,
   * the client is expected to send this first (after the AUTH string is sent).
   * sasl_client_start() may in fact return SASL_OK in this case.
   */
  client_start = olen;

  mutt_message _("Authenticating (SASL)...");

  bufsize = ((olen * 2) > LONG_STRING) ? (olen * 2) : LONG_STRING;
  buf = safe_malloc (bufsize);

  snprintf (buf, bufsize, "AUTH %s", mech);
  olen = strlen (buf);

  /* looping protocol */
  FOREVER
  {
    strfcpy (buf + olen, "\r\n", bufsize - olen);
    mutt_socket_write (pop_data->conn, buf);
    if (mutt_socket_readln (inbuf, sizeof (inbuf), pop_data->conn) < 0)
    {
      sasl_dispose (&saslconn);
      pop_data->status = POP_DISCONNECTED;
      FREE (&buf);
      return POP_A_SOCKET;
    }

    /* Note we don't exit if rc==SASL_OK when client_start is true.
     * This is because the first loop has only sent the AUTH string, we
     * need to loop at least once more to send the pc/olen returned
     * by sasl_client_start().
     */
    if (!client_start && rc != SASL_CONTINUE)
      break;

    if (!mutt_strncmp (inbuf, "+ ", 2)
        && sasl_decode64 (inbuf+2, strlen (inbuf+2), buf, bufsize - 1, &len) != SASL_OK)
    {
      dprint (1, (debugfile, "pop_auth_sasl: error base64-decoding server response.\n"));
      goto bail;
    }

    if (!client_start)
      FOREVER
      {
	rc = sasl_client_step (saslconn, buf, len, &interaction, &pc, &olen);
	if (rc != SASL_INTERACT)
	  break;
	mutt_sasl_interact (interaction);
      }
    else
    {
      olen = client_start;
      client_start = 0;
    }

    /* Even if sasl_client_step() returns SASL_OK, we should send at
     * least one more line to the server.  See #3862.
     */
    if (rc != SASL_CONTINUE && rc != SASL_OK)
      break;

    /* send out response, or line break if none needed */
    if (pc)
    {
      if ((olen * 2) > bufsize)
      {
        bufsize = olen * 2;
        safe_realloc (&buf, bufsize);
      }
      if (sasl_encode64 (pc, olen, buf, bufsize, &olen) != SASL_OK)
      {
	dprint (1, (debugfile, "pop_auth_sasl: error base64-encoding client response.\n"));
	goto bail;
      }
    }
  }

  if (rc != SASL_OK)
    goto bail;

  if (!mutt_strncmp (inbuf, "+OK", 3))
  {
    mutt_sasl_setup_conn (pop_data->conn, saslconn);
    FREE (&buf);
    return POP_A_SUCCESS;
  }

bail:
  sasl_dispose (&saslconn);

  /* terminate SASL session if the last response is not +OK nor -ERR */
  if (!mutt_strncmp (inbuf, "+ ", 2))
  {
    snprintf (buf, bufsize, "*\r\n");
    if (pop_query (pop_data, buf, sizeof (buf)) == -1)
    {
      FREE (&buf);
      return POP_A_SOCKET;
    }
  }

  FREE (&buf);
  mutt_error _("SASL authentication failed.");
  mutt_sleep (2);

  return POP_A_FAILURE;
}
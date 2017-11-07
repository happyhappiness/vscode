static pop_auth_res_t pop_auth_sasl (POP_DATA *pop_data, const char *method)
{
  sasl_conn_t *saslconn;
  sasl_interact_t *interaction = NULL;
  int rc;
  char buf[LONG_STRING];
  char inbuf[LONG_STRING];
  const char* mech;
  char* pc = NULL;
  unsigned int len, olen;
  unsigned char client_start;

  if (mutt_sasl_client_new (pop_data->conn, &saslconn) < 0)
  {
    dprint (1, (debugfile, "pop_auth_sasl: Error allocating SASL connection.\n"));
    return POP_A_FAILURE;
  }

  if (!method)
    method = pop_data->auth_list;

  FOREVER
  {
    rc = sasl_client_start (saslconn, method, NULL,
			    &interaction, &pc, &olen, &mech);
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

  client_start = (olen > 0);

  mutt_message _("Authenticating (SASL)...");

  snprintf (buf, sizeof (buf), "AUTH %s", mech);
  olen = strlen (buf);

  /* looping protocol */
  FOREVER
  {
    strfcpy (buf + olen, "\r\n", sizeof (buf) - olen);
    mutt_socket_write (pop_data->conn, buf);
    if (mutt_socket_readln (inbuf, sizeof (inbuf), pop_data->conn) < 0)
    {
      sasl_dispose (&saslconn);
      pop_data->status = POP_DISCONNECTED;
      return POP_A_SOCKET;
    }

    if (rc != SASL_CONTINUE)
      break;

    if (mutt_strncmp (inbuf, "+ ", 2))
      goto bail;

    if (sasl_decode64 (inbuf, strlen (inbuf), buf, &len) != SASL_OK)
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
      client_start = 0;

    if (rc != SASL_CONTINUE && (olen == 0 || rc != SASL_OK))
      break;

    /* send out response, or line break if none needed */
    if (pc)
    {
      if (sasl_encode64 (pc, olen, buf, sizeof (buf), &olen) != SASL_OK)
      {
	dprint (1, (debugfile, "pop_auth_sasl: error base64-encoding client response.\n"));
	goto bail;
      }

      /* sasl_client_st(art|ep) allocate pc with malloc, expect me to 
       * free it */
      safe_free ((void *) &pc);
    }
  }

  if (rc != SASL_OK)
    goto bail;

  if (!mutt_strncmp (inbuf, "+OK", 3))
  {
    mutt_sasl_setup_conn (pop_data->conn, saslconn);
    return POP_A_SUCCESS;
  }

bail:
  sasl_dispose (&saslconn);

  /* terminate SASL sessoin if the last responce is not +OK nor -ERR */
  if (!mutt_strncmp (inbuf, "+ ", 2))
  {
    snprintf (buf, sizeof (buf), "*\r\n");
    if (pop_query (pop_data, buf, sizeof (buf)) == -1)
      return POP_A_SOCKET;
  }

  mutt_error _("SASL authentication failed.");
  mutt_sleep (2);

  return POP_A_FAILURE;
}
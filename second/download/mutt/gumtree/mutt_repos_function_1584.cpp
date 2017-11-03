int pop_open_connection (POP_DATA *pop_data)
{
  int ret;
  unsigned int n, size;
  char buf[LONG_STRING];

  ret = pop_connect (pop_data);
  if (ret < 0)
  {
    mutt_sleep (2);
    return ret;
  }

  ret = pop_capabilities (pop_data, 0);
  if (ret == -1)
    goto err_conn;
  if (ret == -2)
  {
    mutt_sleep (2);
    return -2;
  }

#if defined(USE_SSL)
  /* Attempt STLS if available and desired. */
  if (!pop_data->conn->ssf && (pop_data->cmd_stls || option(OPTSSLFORCETLS)))
  {
    if (option(OPTSSLFORCETLS))
      pop_data->use_stls = 2;
    if (pop_data->use_stls == 0)
    {
      ret = query_quadoption (OPT_SSLSTARTTLS,
	    _("Secure connection with TLS?"));
      if (ret == -1)
	return -2;
      pop_data->use_stls = 1;
      if (ret == MUTT_YES)
	pop_data->use_stls = 2;
    }
    if (pop_data->use_stls == 2)
    {
      strfcpy (buf, "STLS\r\n", sizeof (buf));
      ret = pop_query (pop_data, buf, sizeof (buf));
      if (ret == -1)
	goto err_conn;
      if (ret != 0)
      {
	mutt_error ("%s", pop_data->err_msg);
	mutt_sleep (2);
      }
      else if (mutt_ssl_starttls (pop_data->conn))
      {
	mutt_error (_("Could not negotiate TLS connection"));
	mutt_sleep (2);
	return -2;
      }
      else
      {
	/* recheck capabilities after STLS completes */
	ret = pop_capabilities (pop_data, 1);
	if (ret == -1)
	  goto err_conn;
	if (ret == -2)
	{
	  mutt_sleep (2);
	  return -2;
	}
      }
    }
  }

  if (option(OPTSSLFORCETLS) && !pop_data->conn->ssf)
  {
    mutt_error _("Encrypted connection unavailable");
    mutt_sleep (1);
    return -2;
  }
#endif

  ret = pop_authenticate (pop_data);
  if (ret == -1)
    goto err_conn;
  if (ret == -3)
    mutt_clear_error ();
  if (ret != 0)
    return ret;

  /* recheck capabilities after authentication */
  ret = pop_capabilities (pop_data, 2);
  if (ret == -1)
    goto err_conn;
  if (ret == -2)
  {
    mutt_sleep (2);
    return -2;
  }

  /* get total size of mailbox */
  strfcpy (buf, "STAT\r\n", sizeof (buf));
  ret = pop_query (pop_data, buf, sizeof (buf));
  if (ret == -1)
    goto err_conn;
  if (ret == -2)
  {
    mutt_error ("%s", pop_data->err_msg);
    mutt_sleep (2);
    return ret;
  }

  sscanf (buf, "+OK %u %u", &n, &size);
  pop_data->size = size;
  return 0;

err_conn:
  pop_data->status = POP_DISCONNECTED;
  mutt_error _("Server closed connection!");
  mutt_sleep (2);
  return -1;
}
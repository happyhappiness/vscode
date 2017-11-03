void pop_fetch_mail (void)
{
  char buffer[LONG_STRING];
  char msgbuf[SHORT_STRING];
  char *url, *p;
  int i, delanswer, last = 0, msgs, bytes, rset = 0, ret;
  CONNECTION *conn;
  CONTEXT ctx;
  MESSAGE *msg = NULL;
  ACCOUNT acct;
  POP_DATA *pop_data;

  if (!PopHost)
  {
    mutt_error _("POP host is not defined.");
    return;
  }

  url = p = safe_calloc (strlen (PopHost) + 7, sizeof (char));
  if (url_check_scheme (PopHost) == U_UNKNOWN)
  {
    strcpy (url, "pop://");	/* __STRCPY_CHECKED__ */
    p = strchr (url, '\0');
  }
  strcpy (p, PopHost);		/* __STRCPY_CHECKED__ */

  ret = pop_parse_path (url, &acct);
  FREE (&url);
  if (ret)
  {
    mutt_error (_("%s is an invalid POP path"), PopHost);
    return;
  }

  conn = mutt_conn_find (NULL, &acct);
  if (!conn)
    return;

  pop_data = safe_calloc (1, sizeof (POP_DATA));
  pop_data->conn = conn;

  if (pop_open_connection (pop_data) < 0)
  {
    mutt_socket_free (pop_data->conn);
    FREE (&pop_data);
    return;
  }

  conn->data = pop_data;

  mutt_message _("Checking for new messages...");

  /* find out how many messages are in the mailbox. */
  strfcpy (buffer, "STAT\r\n", sizeof (buffer));
  ret = pop_query (pop_data, buffer, sizeof (buffer));
  if (ret == -1)
    goto fail;
  if (ret == -2)
  {
    mutt_error ("%s", pop_data->err_msg);
    goto finish;
  }

  sscanf (buffer, "+OK %d %d", &msgs, &bytes);

  /* only get unread messages */
  if (msgs > 0 && option (OPTPOPLAST))
  {
    strfcpy (buffer, "LAST\r\n", sizeof (buffer));
    ret = pop_query (pop_data, buffer, sizeof (buffer));
    if (ret == -1)
      goto fail;
    if (ret == 0)
      sscanf (buffer, "+OK %d", &last);
  }

  if (msgs <= last)
  {
    mutt_message _("No new mail in POP mailbox.");
    goto finish;
  }

  if (mx_open_mailbox (NONULL (Spoolfile), MUTT_APPEND, &ctx) == NULL)
    goto finish;

  delanswer = query_quadoption (OPT_POPDELETE, _("Delete messages from server?"));

  snprintf (msgbuf, sizeof (msgbuf), _("Reading new messages (%d bytes)..."), bytes);
  mutt_message ("%s", msgbuf);

  for (i = last + 1 ; i <= msgs ; i++)
  {
    if ((msg = mx_open_new_message (&ctx, NULL, MUTT_ADD_FROM)) == NULL)
      ret = -3;
    else
    {
      snprintf (buffer, sizeof (buffer), "RETR %d\r\n", i);
      ret = pop_fetch_data (pop_data, buffer, NULL, fetch_message, msg->fp);
      if (ret == -3)
	rset = 1;

      if (ret == 0 && mx_commit_message (msg, &ctx) != 0)
      {
	rset = 1;
	ret = -3;
      }

      mx_close_message (&ctx, &msg);
    }

    if (ret == 0 && delanswer == MUTT_YES)
    {
      /* delete the message on the server */
      snprintf (buffer, sizeof (buffer), "DELE %d\r\n", i);
      ret = pop_query (pop_data, buffer, sizeof (buffer));
    }

    if (ret == -1)
    {
      mx_close_mailbox (&ctx, NULL);
      goto fail;
    }
    if (ret == -2)
    {
      mutt_error ("%s", pop_data->err_msg);
      break;
    }
    if (ret == -3)
    {
      mutt_error _("Error while writing mailbox!");
      break;
    }

    mutt_message (_("%s [%d of %d messages read]"), msgbuf, i - last, msgs - last);
  }

  mx_close_mailbox (&ctx, NULL);

  if (rset)
  {
    /* make sure no messages get deleted */
    strfcpy (buffer, "RSET\r\n", sizeof (buffer));
    if (pop_query (pop_data, buffer, sizeof (buffer)) == -1)
      goto fail;
  }

finish:
  /* exit gracefully */
  strfcpy (buffer, "QUIT\r\n", sizeof (buffer));
  if (pop_query (pop_data, buffer, sizeof (buffer)) == -1)
    goto fail;
  mutt_socket_close (conn);
  FREE (&pop_data);
  return;

fail:
  mutt_error _("Server closed connection!");
  mutt_socket_close (conn);
  FREE (&pop_data);
}
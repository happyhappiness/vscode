static pop_auth_res_t pop_auth_user (POP_DATA *pop_data, const char *method)
{
  char buf[LONG_STRING];
  int ret;

  if (!pop_data->cmd_user)
    return POP_A_UNAVAIL;

  mutt_message _("Logging in...");

  snprintf (buf, sizeof (buf), "USER %s\r\n", pop_data->conn->account.user);
  ret = pop_query (pop_data, buf, sizeof (buf));

  if (pop_data->cmd_user == 2)
  {
    if (ret == 0)
    {
      pop_data->cmd_user = 1;

      dprint (1, (debugfile, "pop_auth_user: set USER capability\n"));
    }

    if (ret == -2)
    {
      pop_data->cmd_user = 0;

      dprint (1, (debugfile, "pop_auth_user: unset USER capability\n"));
      snprintf (pop_data->err_msg, sizeof (pop_data->err_msg),
              _("Command USER is not supported by server."));
    }
  }

  if (ret == 0)
  {
    snprintf (buf, sizeof (buf), "PASS %s\r\n", pop_data->conn->account.pass);
    ret = pop_query_d (pop_data, buf, sizeof (buf), 
#ifdef DEBUG
	/* don't print the password unless we're at the ungodly debugging level */
	debuglevel < MUTT_SOCK_LOG_FULL ? "PASS *\r\n" :
#endif
	NULL);
  }

  switch (ret)
  {
    case 0:
      return POP_A_SUCCESS;
    case -1:
      return POP_A_SOCKET;
  }

  mutt_error ("%s %s", _("Login failed."), pop_data->err_msg);
  mutt_sleep (2);

  return POP_A_FAILURE;
}
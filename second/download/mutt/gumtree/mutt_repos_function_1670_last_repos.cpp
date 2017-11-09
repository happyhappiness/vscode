static int pop_capabilities (POP_DATA *pop_data, int mode)
{
  char buf[LONG_STRING];

  /* don't check capabilities on reconnect */
  if (pop_data->capabilities)
    return 0;

  /* init capabilities */
  if (mode == 0)
  {
    pop_data->cmd_capa = 0;
    pop_data->cmd_stls = 0;
    pop_data->cmd_user = 0;
    pop_data->cmd_uidl = 0;
    pop_data->cmd_top = 0;
    pop_data->resp_codes = 0;
    pop_data->expire = 1;
    pop_data->login_delay = 0;
    FREE (&pop_data->auth_list);
  }

  /* Execute CAPA command */
  if (mode == 0 || pop_data->cmd_capa)
  {
    strfcpy (buf, "CAPA\r\n", sizeof (buf));
    switch (pop_fetch_data (pop_data, buf, NULL, fetch_capa, pop_data))
    {
      case 0:
      {
	pop_data->cmd_capa = 1;
	break;
      }
      case -1:
	return -1;
    }
  }

  /* CAPA not supported, use defaults */
  if (mode == 0 && !pop_data->cmd_capa)
  {
    pop_data->cmd_user = 2;
    pop_data->cmd_uidl = 2;
    pop_data->cmd_top = 2;

    strfcpy (buf, "AUTH\r\n", sizeof (buf));
    if (pop_fetch_data (pop_data, buf, NULL, fetch_auth, pop_data) == -1)
      return -1;
  }

  /* Check capabilities */
  if (mode == 2)
  {
    char *msg = NULL;

    if (!pop_data->expire)
      msg = _("Unable to leave messages on server.");
    if (!pop_data->cmd_top)
      msg = _("Command TOP is not supported by server.");
    if (!pop_data->cmd_uidl)
      msg = _("Command UIDL is not supported by server.");
    if (msg && pop_data->cmd_capa)
    {
      mutt_error (msg);
      return -2;
    }
    pop_data->capabilities = 1;
  }

  return 0;
}
static int fetch_capa (char *line, void *data)
{
  POP_DATA *pop_data = (POP_DATA *)data;
  char *c;

  if (!ascii_strncasecmp (line, "SASL", 4))
  {
    FREE (&pop_data->auth_list);
    c = skip_email_wsp(line + 4);
    pop_data->auth_list = safe_strdup (c);
  }

  else if (!ascii_strncasecmp (line, "STLS", 4))
    pop_data->cmd_stls = 1;

  else if (!ascii_strncasecmp (line, "USER", 4))
    pop_data->cmd_user = 1;

  else if (!ascii_strncasecmp (line, "UIDL", 4))
    pop_data->cmd_uidl = 1;

  else if (!ascii_strncasecmp (line, "TOP", 3))
    pop_data->cmd_top = 1;

  return 0;
}
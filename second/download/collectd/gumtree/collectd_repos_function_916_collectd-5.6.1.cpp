static int powerdns_config_add_server (oconfig_item_t *ci) /* {{{ */
{
  char *socket_temp;

  list_item_t *item;
  int status;

  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING))
  {
    WARNING ("powerdns plugin: `%s' needs exactly one string argument.",
	ci->key);
    return (-1);
  }

  item = calloc (1, sizeof (*item));
  if (item == NULL)
  {
    ERROR ("powerdns plugin: calloc failed.");
    return (-1);
  }

  item->instance = strdup (ci->values[0].value.string);
  if (item->instance == NULL)
  {
    ERROR ("powerdns plugin: strdup failed.");
    sfree (item);
    return (-1);
  }

  /*
   * Set default values for the members of list_item_t
   */
  if (strcasecmp ("Server", ci->key) == 0)
  {
    item->server_type = SRV_AUTHORITATIVE;
    item->func = powerdns_read_server;
    item->socktype = SOCK_STREAM;
    socket_temp = strdup (SERVER_SOCKET);
  }
  else if (strcasecmp ("Recursor", ci->key) == 0)
  {
    item->server_type = SRV_RECURSOR;
    item->func = powerdns_read_recursor;
    item->socktype = SOCK_DGRAM;
    socket_temp = strdup (RECURSOR_SOCKET);
  }
  else
  {
    /* We must never get here.. */
    assert (0);
    return (-1);
  }

  status = 0;
  for (int i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *option = ci->children + i;

    if (strcasecmp ("Collect", option->key) == 0)
      status = powerdns_config_add_collect (item, option);
    else if (strcasecmp ("Socket", option->key) == 0)
      status = cf_util_get_string (option, &socket_temp);
    else
    {
      ERROR ("powerdns plugin: Option `%s' not allowed here.", option->key);
      status = -1;
    }

    if (status != 0)
      break;
  }

  while (status == 0)
  {
    llentry_t *e;

    if (socket_temp == NULL)
    {
      ERROR ("powerdns plugin: socket_temp == NULL.");
      status = -1;
      break;
    }

    item->sockaddr.sun_family = AF_UNIX;
    sstrncpy (item->sockaddr.sun_path, socket_temp,
      sizeof (item->sockaddr.sun_path));

    e = llentry_create (item->instance, item);
    if (e == NULL)
    {
      ERROR ("powerdns plugin: llentry_create failed.");
      status = -1;
      break;
    }
    llist_append (list, e);

    break;
  }

  if (status != 0)
  {
    sfree (socket_temp);
    sfree (item);
    return (-1);
  }

  DEBUG ("powerdns plugin: Add server: instance = %s;", item->instance);

  sfree (socket_temp);
  return (0);
}
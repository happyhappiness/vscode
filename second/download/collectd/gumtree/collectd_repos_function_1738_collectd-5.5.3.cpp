static int mb_config_add_host (oconfig_item_t *ci) /* {{{ */
{
  mb_host_t *host;
  int status;
  int i;

  host = malloc (sizeof (*host));
  if (host == NULL)
    return (ENOMEM);
  memset (host, 0, sizeof (*host));
  host->slaves = NULL;

  status = cf_util_get_string_buffer (ci, host->host, sizeof (host->host));
  if (status != 0)
  {
    sfree (host);
    return (status);
  }
  if (host->host[0] == 0)
  {
    sfree (host);
    return (EINVAL);
  }

  for (i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *child = ci->children + i;
    status = 0;

    if (strcasecmp ("Address", child->key) == 0)
    {
      char buffer[NI_MAXHOST];
      status = cf_util_get_string_buffer (child, buffer, sizeof (buffer));
      if (status == 0)
        status = mb_config_set_host_address (host, buffer);
      if (status == 0)
        host->conntype = MBCONN_TCP;
    }
    else if (strcasecmp ("Port", child->key) == 0)
    {
      host->port = cf_util_get_port_number (child);
      if (host->port <= 0)
        status = -1;
    }
    else if (strcasecmp ("Device", child->key) == 0)
    {
      status = cf_util_get_string_buffer (child, host->node, sizeof (host->node));
      if (status == 0)
        host->conntype = MBCONN_RTU;
    }
    else if (strcasecmp ("Baudrate", child->key) == 0)
      status = cf_util_get_int(child, &host->baudrate);
    else if (strcasecmp ("Interval", child->key) == 0)
      status = cf_util_get_cdtime (child, &host->interval);
    else if (strcasecmp ("Slave", child->key) == 0)
      /* Don't set status: Gracefully continue if a slave fails. */
      mb_config_add_slave (host, child);
    else
    {
      ERROR ("Modbus plugin: Unknown configuration option: %s", child->key);
      status = -1;
    }

    if (status != 0)
      break;
  } /* for (i = 0; i < ci->children_num; i++) */

  assert (host->host[0] != 0);
  if (host->node[0] == 0)
  {
    ERROR ("Modbus plugin: Data block \"%s\": No address or device has been specified.",
        host->host);
    status = -1;
  }
  if (host->conntype == MBCONN_RTU && !host->baudrate)
  {
    ERROR ("Modbus plugin: Data block \"%s\": No serial baudrate has been specified.",
        host->host);
    status = -1;
  }
  if ((host->conntype == MBCONN_TCP && host->baudrate) ||
      (host->conntype == MBCONN_RTU && host->port))
  {
    ERROR ("Modbus plugin: Data block \"%s\": You've mixed up RTU and TCP options.",
        host->host);
    status = -1;
  }

  if (status == 0)
  {
    user_data_t ud;
    char name[1024];
    struct timespec interval = { 0, 0 };

    ud.data = host;
    ud.free_func = host_free;

    ssnprintf (name, sizeof (name), "modbus-%s", host->host);

    CDTIME_T_TO_TIMESPEC (host->interval, &interval);

    plugin_register_complex_read (/* group = */ NULL, name,
        /* callback = */ mb_read,
        /* interval = */ (host->interval > 0) ? &interval : NULL,
        &ud);
  }
  else
  {
    host_free (host);
  }

  return (status);
}
static int mb_init_connection (mb_host_t *host) /* {{{ */
{
  int status;

  if (host == NULL)
    return (EINVAL);

  if (host->is_connected)
    return (0);

  /* Only reconnect once per interval. */
  if (host->have_reconnected)
    return (-1);

  modbus_set_debug (&host->connection, 1);

#if 0
  /* We'll do the error handling ourselves. */
  modbus_set_error_handling (&host->connection, NOP_ON_ERROR);
#endif

  if ((host->port < 1) || (host->port > 65535))
    host->port = MODBUS_TCP_DEFAULT_PORT;

  DEBUG ("Modbus plugin: Trying to connect to \"%s\", port %i.",
      host->node, host->port);

  modbus_init_tcp (&host->connection,
      /* host = */ host->node);
#if 0
      /* port = */ host->port);
#endif

  status = modbus_connect (&host->connection);
  if (status != 0)
  {
    ERROR ("Modbus plugin: modbus_connect (%s, %i) failed with status %i.",
        host->node, host->port, status);
    return (status);
  }

  host->is_connected = 1;
  host->have_reconnected = 1;
  return (0);
}
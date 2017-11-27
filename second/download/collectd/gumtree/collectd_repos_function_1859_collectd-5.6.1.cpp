static int mb_init_connection (mb_host_t *host) /* {{{ */
{
  int status;

  if (host == NULL)
    return (EINVAL);

  if (host->connection != NULL)
    return (0);

  if (host->conntype == MBCONN_TCP)
  {
    if ((host->port < 1) || (host->port > 65535))
      host->port = MODBUS_TCP_DEFAULT_PORT;

    DEBUG ("Modbus plugin: Trying to connect to \"%s\", port %i.",
        host->node, host->port);

    host->connection = modbus_new_tcp (host->node, host->port);
    if (host->connection == NULL)
    {
      ERROR ("Modbus plugin: Creating new Modbus/TCP object failed.");
      return (-1);
    }
  }
  else
  {
    DEBUG ("Modbus plugin: Trying to connect to \"%s\", baudrate %i.",
        host->node, host->baudrate);

    host->connection = modbus_new_rtu (host->node, host->baudrate, 'N', 8, 1);
    if (host->connection == NULL)
    {
      ERROR ("Modbus plugin: Creating new Modbus/RTU object failed.");
      return (-1);
    }
  }

#if COLLECT_DEBUG
  modbus_set_debug (host->connection, 1);
#endif

  /* We'll do the error handling ourselves. */
  modbus_set_error_recovery (host->connection, 0);

  status = modbus_connect (host->connection);
  if (status != 0)
  {
    ERROR ("Modbus plugin: modbus_connect (%s, %i) failed with status %i.",
        host->node, host->port ? host->port : host->baudrate, status);
    modbus_free (host->connection);
    host->connection = NULL;
    return (status);
  }

  return (0);
}
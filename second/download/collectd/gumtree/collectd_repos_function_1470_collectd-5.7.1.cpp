static void tt_open_db(void) {
  const char *host;
  int port = DEFAULT_PORT;

  if (rdb != NULL)
    return;

  host = ((config_host != NULL) ? config_host : DEFAULT_HOST);

  if (config_port != NULL) {
    port = service_name_to_port_number(config_port);
    if (port <= 0)
      return;
  }

  rdb = tcrdbnew();
  if (rdb == NULL)
    return;
  else if (!tcrdbopen(rdb, host, port)) {
    printerr();
    tcrdbdel(rdb);
    rdb = NULL;
  }
}
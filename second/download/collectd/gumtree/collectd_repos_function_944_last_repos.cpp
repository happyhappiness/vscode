static int conn_config(const char *key, const char *value) {
  if (strcasecmp(key, "ListeningPorts") == 0) {
    if (IS_TRUE(value))
      port_collect_listening = 1;
    else
      port_collect_listening = 0;
  } else if ((strcasecmp(key, "LocalPort") == 0) ||
             (strcasecmp(key, "RemotePort") == 0)) {
    port_entry_t *pe;
    int port = atoi(value);

    if ((port < 1) || (port > 65535)) {
      ERROR("tcpconns plugin: Invalid port: %i", port);
      return 1;
    }

    pe = conn_get_port_entry((uint16_t)port, 1 /* create */);
    if (pe == NULL) {
      ERROR("tcpconns plugin: conn_get_port_entry failed.");
      return 1;
    }

    if (strcasecmp(key, "LocalPort") == 0)
      pe->flags |= PORT_COLLECT_LOCAL;
    else
      pe->flags |= PORT_COLLECT_REMOTE;
  } else if (strcasecmp(key, "AllPortsSummary") == 0) {
    if (IS_TRUE(value))
      port_collect_total = 1;
    else
      port_collect_total = 0;
  } else {
    return -1;
  }

  return 0;
}
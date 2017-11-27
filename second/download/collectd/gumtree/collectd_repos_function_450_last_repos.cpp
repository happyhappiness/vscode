static port_list_t *ovs_stats_get_port(const char *uuid) {
  if (uuid == NULL)
    return NULL;

  for (port_list_t *port = g_port_list_head; port != NULL; port = port->next) {
    if (strncmp(port->port_uuid, uuid, strlen(port->port_uuid)) == 0)
      return port;
  }
  return NULL;
}
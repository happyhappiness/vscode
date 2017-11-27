static port_list_t *ovs_stats_get_port_by_name(const char *name) {
  if (name == NULL)
    return NULL;

  for (port_list_t *port = g_port_list_head; port != NULL; port = port->next)
    if ((strncmp(port->name, name, strlen(port->name)) == 0) &&
        strlen(name) == strlen(port->name))
      return port;
  return NULL;
}
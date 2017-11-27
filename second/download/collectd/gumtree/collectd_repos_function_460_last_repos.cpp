static int ovs_stats_del_port(const char *uuid) {
  port_list_t *prev_port = g_port_list_head;
  for (port_list_t *port = g_port_list_head; port != NULL;
       prev_port = port, port = port->next) {
    if (strncmp(port->port_uuid, uuid, strlen(port->port_uuid)) == 0) {
      if (port == g_port_list_head)
        g_port_list_head = port->next;
      else
        prev_port->next = port->next;
      sfree(port);
      break;
    }
  }
  return 0;
}
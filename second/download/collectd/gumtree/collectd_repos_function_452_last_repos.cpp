static port_list_t *ovs_stats_new_port(bridge_list_t *bridge,
                                       const char *uuid) {
  port_list_t *port = ovs_stats_get_port(uuid);

  if (port == NULL) {
    port = (port_list_t *)calloc(1, sizeof(port_list_t));
    if (!port) {
      ERROR("%s: Error allocating port", plugin_name);
      return NULL;
    }
    memset(port->stats, -1, sizeof(int64_t[IFACE_COUNTER_COUNT]));
    sstrncpy(port->port_uuid, uuid, sizeof(port->port_uuid));
    pthread_mutex_lock(&g_stats_lock);
    port->next = g_port_list_head;
    g_port_list_head = port;
    pthread_mutex_unlock(&g_stats_lock);
  }
  if (bridge != NULL) {
    pthread_mutex_lock(&g_stats_lock);
    port->br = bridge;
    pthread_mutex_unlock(&g_stats_lock);
  }
  return port;
}
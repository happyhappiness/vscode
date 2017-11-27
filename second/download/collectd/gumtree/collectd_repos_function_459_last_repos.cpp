static int ovs_stats_update_port(const char *uuid, yajl_val port) {
  const char *new[] = {"new", NULL};
  const char *name[] = {"name", NULL};
  yajl_val row;
  port_list_t *portentry = NULL;
  if (port && YAJL_IS_OBJECT(port)) {
    row = yajl_tree_get(port, new, yajl_t_object);
    if (row && YAJL_IS_OBJECT(row)) {
      yajl_val port_name = yajl_tree_get(row, name, yajl_t_string);
      if (port_name && YAJL_IS_STRING(port_name)) {
        portentry = ovs_stats_get_port(uuid);
        if (portentry == NULL)
          portentry = ovs_stats_new_port(NULL, uuid);
        if (portentry) {
          pthread_mutex_lock(&g_stats_lock);
          sstrncpy(portentry->name, YAJL_GET_STRING(port_name),
                   sizeof(portentry->name));
          pthread_mutex_unlock(&g_stats_lock);
        }
      }
    }
  } else {
    ERROR("Incorrect JSON Port data");
    return -1;
  }
  return 0;
}
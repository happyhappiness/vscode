static int ovs_stats_update_bridge(yajl_val bridge) {
  const char *new[] = {"new", NULL};
  const char *name[] = {"name", NULL};
  const char *ports[] = {"ports", NULL};
  bridge_list_t *br = NULL;

  if (bridge && YAJL_IS_OBJECT(bridge)) {
    yajl_val row = yajl_tree_get(bridge, new, yajl_t_object);
    if (row && YAJL_IS_OBJECT(row)) {
      yajl_val br_name = yajl_tree_get(row, name, yajl_t_string);
      yajl_val br_ports = yajl_tree_get(row, ports, yajl_t_array);
      if (br_name && YAJL_IS_STRING(br_name)) {
        br = ovs_stats_get_bridge(g_bridge_list_head, YAJL_GET_STRING(br_name));
        pthread_mutex_lock(&g_stats_lock);
        if (br == NULL) {
          br = calloc(1, sizeof(*br));
          if (!br) {
            pthread_mutex_unlock(&g_stats_lock);
            ERROR("%s: calloc(%zu) failed.", plugin_name, sizeof(*br));
            return -1;
          }
          char *tmp = YAJL_GET_STRING(br_name);

          if (tmp != NULL)
            br->name = strdup(tmp);
          if (br->name == NULL) {
            sfree(br);
            pthread_mutex_unlock(&g_stats_lock);
            ERROR("%s: strdup failed.", plugin_name);
            return -1;
          }
          br->next = g_bridge_list_head;
          g_bridge_list_head = br;
        }
        pthread_mutex_unlock(&g_stats_lock);
      }
      if (br_ports && YAJL_IS_ARRAY(br_ports)) {
        char *tmp = YAJL_GET_STRING(br_ports->u.array.values[0]);
        if (tmp != NULL && strcmp("set", tmp) == 0) {
          yajl_val *array = YAJL_GET_ARRAY(br_ports)->values;
          size_t array_len = YAJL_GET_ARRAY(br_ports)->len;
          if (array != NULL && array_len > 0 && YAJL_IS_ARRAY(array[1])) {
            yajl_val *ports_arr = YAJL_GET_ARRAY(array[1])->values;
            size_t ports_num = YAJL_GET_ARRAY(array[1])->len;
            for (size_t i = 0; i < ports_num && ports_arr != NULL; i++)
              ovs_stats_new_port(
                  br, YAJL_GET_STRING(ports_arr[i]->u.array.values[1]));
          }
        } else
          ovs_stats_new_port(br, YAJL_GET_STRING(br_ports->u.array.values[1]));
      }
    }
  } else {
    ERROR("Incorrect JSON Bridge data");
    return -1;
  }
  return 0;
}
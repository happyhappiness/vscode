static int ovs_stats_del_bridge(yajl_val bridge) {
  const char *old[] = {"old", NULL};
  const char *name[] = {"name", NULL};

  yajl_val row;

  if (bridge && YAJL_IS_OBJECT(bridge)) {
    row = yajl_tree_get(bridge, old, yajl_t_object);
    if (row && YAJL_IS_OBJECT(row)) {
      yajl_val br_name = yajl_tree_get(row, name, yajl_t_string);
      if (br_name && YAJL_IS_STRING(br_name)) {
        bridge_list_t *prev_br = g_bridge_list_head;
        for (bridge_list_t *br = g_bridge_list_head; br != NULL;
             prev_br = br, br = br->next) {
          if ((strncmp(br->name, br_name->u.string, strlen(br->name)) == 0) &&
              strlen(br->name) == strlen(br_name->u.string)) {
            if (br == g_bridge_list_head)
              g_bridge_list_head = br->next;
            else
              prev_br->next = br->next;
            sfree(br->name);
            sfree(br);
            break;
          }
        }
      }
    }
  } else
    WARNING("%s: Incorrect data for deleting bridge", plugin_name);
  return 0;
}
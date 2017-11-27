static bridge_list_t *ovs_stats_get_bridge(bridge_list_t *head,
                                           const char *name) {
  if (name == NULL)
    return NULL;

  for (bridge_list_t *bridge = head; bridge != NULL; bridge = bridge->next) {
    if ((strncmp(bridge->name, name, strlen(bridge->name)) == 0) &&
        strlen(name) == strlen(bridge->name))
      return bridge;
  }
  return NULL;
}
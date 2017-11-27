static int ovs_stats_is_monitored_bridge(const char *br_name) {
  /* if no bridges are configured, return true */
  if (g_monitored_bridge_list_head == NULL)
    return 1;

  /* check if given bridge exists */
  if (ovs_stats_get_bridge(g_monitored_bridge_list_head, br_name) != NULL)
    return 1;

  return 0;
}
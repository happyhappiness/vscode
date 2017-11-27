static int olsrd_config(const char *key, const char *value) /* {{{ */
{
  if (strcasecmp("Host", key) == 0)
    olsrd_set_node(value);
  else if (strcasecmp("Port", key) == 0)
    olsrd_set_service(value);
  else if (strcasecmp("CollectLinks", key) == 0)
    olsrd_set_detail(&config_want_links, value, key);
  else if (strcasecmp("CollectRoutes", key) == 0)
    olsrd_set_detail(&config_want_routes, value, key);
  else if (strcasecmp("CollectTopology", key) == 0)
    olsrd_set_detail(&config_want_topology, value, key);
  else {
    ERROR("olsrd plugin: Unknown configuration option given: %s", key);
    return (-1);
  }

  return (0);
}
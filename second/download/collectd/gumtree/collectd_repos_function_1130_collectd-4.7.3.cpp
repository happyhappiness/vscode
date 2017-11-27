static int network_config (oconfig_item_t *ci) /* {{{ */
{
  int i;

  for (i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp ("Listen", child->key) == 0)
      network_config_add_listen (child);
    else if (strcasecmp ("Server", child->key) == 0)
      network_config_add_server (child);
    else if (strcasecmp ("TimeToLive", child->key) == 0)
      network_config_set_ttl (child);
    else if (strcasecmp ("Forward", child->key) == 0)
      network_config_set_boolean (child, &network_config_forward);
    else if (strcasecmp ("CacheFlush", child->key) == 0)
      network_config_set_cache_flush (child);
    else
    {
      WARNING ("network plugin: Option `%s' is not allowed here.",
          child->key);
    }
  }

  return (0);
}
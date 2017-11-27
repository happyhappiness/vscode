static int plugin_config (oconfig_item_t *ci) /* {{{ */
{
  int i;
  
  /* The lock should not be necessary in the config callback, but let's be
   * sure.. */
  pthread_mutex_lock (&stat_nodes_lock);

  for (i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp ("Address", child->key) == 0)
      cf_util_get_string (child, &conf_node);
    else if (strcasecmp ("Port", child->key) == 0)
      cf_util_get_service (child, &conf_service);
    else if (strcasecmp ("View", child->key) == 0)
      pinba_config_view (child);
    else
      WARNING ("pinba plugin: Unknown config option: %s", child->key);
  }

  pthread_mutex_unlock(&stat_nodes_lock);
  
  return (0);
}
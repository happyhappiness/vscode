static int redis_config (oconfig_item_t *ci) /* {{{ */
{
  int i;

  for (i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *option = ci->children + i;

    if (strcasecmp ("Node", option->key) == 0)
      redis_config_node (option);
    else
      WARNING ("redis plugin: Option `%s' not allowed in redis"
          " configuration. It will be ignored.", option->key);
  }

  if (nodes_head == NULL)
  {
    ERROR ("redis plugin: No valid node configuration could be found.");
    return (ENOENT);
  }

  return (0);
}
static int gmond_config(oconfig_item_t *ci) /* {{{ */
{
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;
    if (strcasecmp("MCReceiveFrom", child->key) == 0)
      gmond_config_set_address(child, &mc_receive_group, &mc_receive_port);
    else if (strcasecmp("Metric", child->key) == 0)
      gmond_config_add_metric(child);
    else {
      WARNING("gmond plugin: Unknown configuration option `%s' ignored.",
              child->key);
    }
  }

  return (0);
}
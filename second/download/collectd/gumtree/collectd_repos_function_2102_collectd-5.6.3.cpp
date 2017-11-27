static int wt_config(oconfig_item_t *ci) {
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Node", child->key) == 0)
      wt_config_tsd(child);
    else {
      ERROR("write_tsdb plugin: Invalid configuration "
            "option: %s.",
            child->key);
    }
  }

  return 0;
}
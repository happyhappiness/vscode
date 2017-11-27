static int wt_config(oconfig_item_t *ci) {
  if ((resolve_interval == 0) && (resolve_jitter == 0))
    resolve_interval = resolve_jitter = plugin_get_interval();

  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Node", child->key) == 0)
      wt_config_tsd(child);
    else if (strcasecmp("ResolveInterval", child->key) == 0)
      cf_util_get_cdtime(child, &resolve_interval);
    else if (strcasecmp("ResolveJitter", child->key) == 0)
      cf_util_get_cdtime(child, &resolve_jitter);
    else {
      ERROR("write_tsdb plugin: Invalid configuration "
            "option: %s.",
            child->key);
    }
  }

  return 0;
}
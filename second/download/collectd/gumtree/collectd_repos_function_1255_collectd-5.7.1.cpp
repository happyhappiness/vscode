int latency_config(latency_config_t *conf, oconfig_item_t *ci,
                   char const *plugin) {
  int status = 0;

  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Percentile", child->key) == 0)
      status = latency_config_add_percentile(conf, child, plugin);
    else if (strcasecmp("Bucket", child->key) == 0)
      status = latency_config_add_bucket(conf, child, plugin);
    else
      WARNING("%s plugin: \"%s\" is not a valid option within a \"%s\" block.",
              plugin, child->key, ci->key);

    if (status != 0)
      return status;
  }

  if ((status == 0) && (conf->percentile_num == 0) &&
      (conf->buckets_num == 0)) {
    ERROR("%s plugin: The \"%s\" block must contain at least one "
          "\"Percentile\" or \"Bucket\" option.",
          plugin, ci->key);
    return EINVAL;
  }

  return 0;
}
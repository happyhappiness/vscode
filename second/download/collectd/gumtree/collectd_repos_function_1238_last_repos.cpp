static int hp_config(oconfig_item_t *ci) {
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;
    if (strcasecmp("ReportPerNodeHP", child->key) == 0)
      cf_util_get_boolean(child, &g_flag_rpt_numa);
    else if (strcasecmp("ReportRootHP", child->key) == 0)
      cf_util_get_boolean(child, &g_flag_rpt_mm);
    else if (strcasecmp("ValuesPages", child->key) == 0)
      cf_util_get_boolean(child, &g_values_pages);
    else if (strcasecmp("ValuesBytes", child->key) == 0)
      cf_util_get_boolean(child, &g_values_bytes);
    else if (strcasecmp("ValuesPercentage", child->key) == 0)
      cf_util_get_boolean(child, &g_values_percent);
    else
      ERROR("%s: Invalid configuration option: \"%s\".", g_plugin_name,
            child->key);
  }

  return 0;
}
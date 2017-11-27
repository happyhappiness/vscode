static int battery_config(oconfig_item_t *ci) {
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("ValuesPercentage", child->key) == 0)
      cf_util_get_boolean(child, &report_percent);
    else if (strcasecmp("ReportDegraded", child->key) == 0)
      cf_util_get_boolean(child, &report_degraded);
    else if (strcasecmp("QueryStateFS", child->key) == 0)
      cf_util_get_boolean(child, &query_statefs);
    else
      WARNING("battery plugin: Ignoring unknown "
              "configuration option \"%s\".",
              child->key);
  }

  return (0);
}
static int prom_config(oconfig_item_t *ci) {
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Port", child->key) == 0) {
      int status = cf_util_get_port_number(child);
      if (status > 0)
        httpd_port = (unsigned short)status;
    } else if (strcasecmp("StalenessDelta", child->key) == 0) {
      cf_util_get_cdtime(child, &staleness_delta);
    } else {
      WARNING("write_prometheus plugin: Ignoring unknown configuration option "
              "\"%s\".",
              child->key);
    }
  }

  return 0;
}
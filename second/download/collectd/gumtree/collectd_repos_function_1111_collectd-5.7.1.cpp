static int cgps_config(oconfig_item_t *ci) {
  int i;

  for (i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Host", child->key) == 0)
      cf_util_get_string(child, &cgps_config_data.host);
    else if (strcasecmp("Port", child->key) == 0)
      cf_util_get_service(child, &cgps_config_data.port);
    else if (strcasecmp("Timeout", child->key) == 0)
      cf_util_get_cdtime(child, &cgps_config_data.timeout);
    else if (strcasecmp("PauseConnect", child->key) == 0)
      cf_util_get_cdtime(child, &cgps_config_data.pause_connect);
    else
      WARNING("gps plugin: Ignoring unknown config option \"%s\".", child->key);
  }

  // Controlling the value for timeout:
  // If set too high it blocks the reading (> 5 s), too low it gets not reading
  // (< 500 us).
  // To avoid any issues we replace "out of range" value by the default value.
  if (cgps_config_data.timeout > TIME_T_TO_CDTIME_T(5) ||
      cgps_config_data.timeout < US_TO_CDTIME_T(500)) {
    WARNING("gps plugin: timeout set to %.6f sec. setting to default (%.6f).",
            CDTIME_T_TO_DOUBLE(cgps_config_data.timeout),
            CDTIME_T_TO_DOUBLE(CGPS_DEFAULT_TIMEOUT));
    cgps_config_data.timeout = CGPS_DEFAULT_TIMEOUT;
  }

  return (0);
}
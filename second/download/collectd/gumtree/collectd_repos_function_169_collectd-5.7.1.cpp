static int rc_config(oconfig_item_t *ci) {
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t const *child = ci->children + i;
    const char *key = child->key;
    int status = 0;

    if (strcasecmp("DataDir", key) == 0) {
      status = cf_util_get_string(child, &datadir);
      if (status == 0) {
        int len = strlen(datadir);

        while ((len > 0) && (datadir[len - 1] == '/')) {
          len--;
          datadir[len] = 0;
        }

        if (len <= 0)
          sfree(datadir);
      }
    } else if (strcasecmp("DaemonAddress", key) == 0)
      status = cf_util_get_string(child, &daemon_address);
    else if (strcasecmp("CreateFiles", key) == 0)
      status = cf_util_get_boolean(child, &config_create_files);
    else if (strcasecmp("CreateFilesAsync", key) == 0)
      status = cf_util_get_boolean(child, &rrdcreate_config.async);
    else if (strcasecmp("CollectStatistics", key) == 0)
      status = cf_util_get_boolean(child, &config_collect_stats);
    else if (strcasecmp("StepSize", key) == 0) {
      int tmp = -1;

      status = rc_config_get_int_positive(child, &tmp);
      if (status == 0)
        rrdcreate_config.stepsize = (unsigned long)tmp;
    } else if (strcasecmp("HeartBeat", key) == 0)
      status = rc_config_get_int_positive(child, &rrdcreate_config.heartbeat);
    else if (strcasecmp("RRARows", key) == 0)
      status = rc_config_get_int_positive(child, &rrdcreate_config.rrarows);
    else if (strcasecmp("RRATimespan", key) == 0) {
      int tmp = -1;
      status = rc_config_get_int_positive(child, &tmp);
      if (status == 0)
        status = rc_config_add_timespan(tmp);
    } else if (strcasecmp("XFF", key) == 0)
      status = rc_config_get_xff(child, &rrdcreate_config.xff);
    else {
      WARNING("rrdcached plugin: Ignoring invalid option %s.", key);
      continue;
    }

    if (status != 0)
      WARNING("rrdcached plugin: Handling the \"%s\" option failed.", key);
  }

  if (daemon_address != NULL) {
    plugin_register_write("rrdcached", rc_write, /* user_data = */ NULL);
    plugin_register_flush("rrdcached", rc_flush, /* user_data = */ NULL);
  }
  return (0);
}
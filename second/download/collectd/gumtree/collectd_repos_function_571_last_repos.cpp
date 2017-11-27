static int sensu_config_node(oconfig_item_t *ci) /* {{{ */
{
  struct sensu_host *host = NULL;
  int status = 0;
  oconfig_item_t *child;
  char callback_name[DATA_MAX_NAME_LEN];

  if ((host = calloc(1, sizeof(*host))) == NULL) {
    ERROR("write_sensu plugin: calloc failed.");
    return ENOMEM;
  }
  pthread_mutex_init(&host->lock, NULL);
  host->reference_count = 1;
  host->node = NULL;
  host->service = NULL;
  host->notifications = 0;
  host->metrics = 0;
  host->store_rates = 1;
  host->always_append_ds = 0;
  host->metric_handlers.nb_strs = 0;
  host->metric_handlers.strs = NULL;
  host->notification_handlers.nb_strs = 0;
  host->notification_handlers.strs = NULL;
  host->separator = strdup("/");
  if (host->separator == NULL) {
    ERROR("write_sensu plugin: Unable to alloc memory");
    sensu_free(host);
    return -1;
  }

  status = cf_util_get_string(ci, &host->name);
  if (status != 0) {
    WARNING("write_sensu plugin: Required host name is missing.");
    sensu_free(host);
    return -1;
  }

  for (int i = 0; i < ci->children_num; i++) {
    child = &ci->children[i];
    status = 0;

    if (strcasecmp("Host", child->key) == 0) {
      status = cf_util_get_string(child, &host->node);
      if (status != 0)
        break;
    } else if (strcasecmp("Notifications", child->key) == 0) {
      status = cf_util_get_boolean(child, &host->notifications);
      if (status != 0)
        break;
    } else if (strcasecmp("Metrics", child->key) == 0) {
      status = cf_util_get_boolean(child, &host->metrics);
      if (status != 0)
        break;
    } else if (strcasecmp("EventServicePrefix", child->key) == 0) {
      status = cf_util_get_string(child, &host->event_service_prefix);
      if (status != 0)
        break;
    } else if (strcasecmp("Separator", child->key) == 0) {
      status = cf_util_get_string(child, &host->separator);
      if (status != 0)
        break;
    } else if (strcasecmp("MetricHandler", child->key) == 0) {
      char *temp_str = NULL;
      status = cf_util_get_string(child, &temp_str);
      if (status != 0)
        break;
      status = add_str_to_list(&(host->metric_handlers), temp_str);
      free(temp_str);
      if (status != 0)
        break;
    } else if (strcasecmp("NotificationHandler", child->key) == 0) {
      char *temp_str = NULL;
      status = cf_util_get_string(child, &temp_str);
      if (status != 0)
        break;
      status = add_str_to_list(&(host->notification_handlers), temp_str);
      free(temp_str);
      if (status != 0)
        break;
    } else if (strcasecmp("Port", child->key) == 0) {
      status = cf_util_get_service(child, &host->service);
      if (status != 0) {
        ERROR("write_sensu plugin: Invalid argument "
              "configured for the \"Port\" "
              "option.");
        break;
      }
    } else if (strcasecmp("StoreRates", child->key) == 0) {
      status = cf_util_get_boolean(child, &host->store_rates);
      if (status != 0)
        break;
    } else if (strcasecmp("AlwaysAppendDS", child->key) == 0) {
      status = cf_util_get_boolean(child, &host->always_append_ds);
      if (status != 0)
        break;
    } else {
      WARNING("write_sensu plugin: ignoring unknown config "
              "option: \"%s\"",
              child->key);
    }
  }
  if (status != 0) {
    sensu_free(host);
    return status;
  }

  if (host->metrics && (host->metric_handlers.nb_strs == 0)) {
    sensu_free(host);
    WARNING("write_sensu plugin: metrics enabled but no MetricHandler defined. "
            "Giving up.");
    return -1;
  }

  if (host->notifications && (host->notification_handlers.nb_strs == 0)) {
    sensu_free(host);
    WARNING("write_sensu plugin: notifications enabled but no "
            "NotificationHandler defined. Giving up.");
    return -1;
  }

  if ((host->notification_handlers.nb_strs > 0) && (host->notifications == 0)) {
    WARNING("write_sensu plugin: NotificationHandler given so forcing "
            "notifications to be enabled");
    host->notifications = 1;
  }

  if ((host->metric_handlers.nb_strs > 0) && (host->metrics == 0)) {
    WARNING("write_sensu plugin: MetricHandler given so forcing metrics to be "
            "enabled");
    host->metrics = 1;
  }

  if (!(host->notifications || host->metrics)) {
    WARNING("write_sensu plugin: neither metrics nor notifications enabled. "
            "Giving up.");
    sensu_free(host);
    return -1;
  }

  snprintf(callback_name, sizeof(callback_name), "write_sensu/%s", host->name);

  user_data_t ud = {.data = host, .free_func = sensu_free};

  pthread_mutex_lock(&host->lock);

  if (host->metrics) {
    status = plugin_register_write(callback_name, sensu_write, &ud);
    if (status != 0)
      WARNING("write_sensu plugin: plugin_register_write (\"%s\") "
              "failed with status %i.",
              callback_name, status);
    else /* success */
      host->reference_count++;
  }

  if (host->notifications) {
    status =
        plugin_register_notification(callback_name, sensu_notification, &ud);
    if (status != 0)
      WARNING("write_sensu plugin: plugin_register_notification (\"%s\") "
              "failed with status %i.",
              callback_name, status);
    else
      host->reference_count++;
  }

  if (host->reference_count <= 1) {
    /* Both callbacks failed => free memory.
     * We need to unlock here, because sensu_free() will lock.
     * This is not a race condition, because we're the only one
     * holding a reference. */
    pthread_mutex_unlock(&host->lock);
    sensu_free(host);
    return -1;
  }

  host->reference_count--;
  pthread_mutex_unlock(&host->lock);

  return status;
}
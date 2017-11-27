static int tcsv_config_add_file(oconfig_item_t *ci) {
  instance_definition_t *id;
  int status = 0;

  /* Registration variables */
  char cb_name[DATA_MAX_NAME_LEN];

  id = calloc(1, sizeof(*id));
  if (id == NULL)
    return -1;
  id->plugin_name = NULL;
  id->instance = NULL;
  id->path = NULL;
  id->metric_list = NULL;
  id->time_from = -1;
  id->next = NULL;

  status = cf_util_get_string(ci, &id->path);
  if (status != 0) {
    sfree(id);
    return status;
  }

  /* Use default interval. */
  id->interval = plugin_get_interval();

  for (int i = 0; i < ci->children_num; ++i) {
    oconfig_item_t *option = ci->children + i;
    status = 0;

    if (strcasecmp("Instance", option->key) == 0)
      status = cf_util_get_string(option, &id->instance);
    else if (strcasecmp("Collect", option->key) == 0)
      status = tcsv_config_add_instance_collect(id, option);
    else if (strcasecmp("Interval", option->key) == 0)
      cf_util_get_cdtime(option, &id->interval);
    else if (strcasecmp("TimeFrom", option->key) == 0)
      status = tcsv_config_get_index(option, &id->time_from);
    else if (strcasecmp("Plugin", option->key) == 0)
      status = cf_util_get_string(option, &id->plugin_name);
    else {
      WARNING("tail_csv plugin: Option `%s' not allowed here.", option->key);
      status = -1;
    }

    if (status != 0)
      break;
  }

  if (status != 0) {
    tcsv_instance_definition_destroy(id);
    return -1;
  }

  /* Verify all necessary options have been set. */
  if (id->path == NULL) {
    WARNING("tail_csv plugin: Option `Path' must be set.");
    status = -1;
  } else if (id->metric_list == NULL) {
    WARNING("tail_csv plugin: Option `Collect' must be set.");
    status = -1;
  }

  if (status != 0) {
    tcsv_instance_definition_destroy(id);
    return -1;
  }

  snprintf(cb_name, sizeof(cb_name), "tail_csv/%s", id->path);

  status = plugin_register_complex_read(
      NULL, cb_name, tcsv_read, id->interval,
      &(user_data_t){
          .data = id, .free_func = tcsv_instance_definition_destroy,
      });
  if (status != 0) {
    ERROR("tail_csv plugin: Registering complex read function failed.");
    return -1;
  }

  return 0;
}
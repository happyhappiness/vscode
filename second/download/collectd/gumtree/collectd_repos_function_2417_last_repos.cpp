static int ts_create(const oconfig_item_t *ci, void **user_data) /* {{{ */
{
  ts_data_t *data;
  int status;

  data = calloc(1, sizeof(*data));
  if (data == NULL) {
    ERROR("ts_create: calloc failed.");
    return -ENOMEM;
  }

  data->host = NULL;
  data->plugin = NULL;
  data->plugin_instance = NULL;
  /* data->type = NULL; */
  data->type_instance = NULL;
  data->meta = NULL;
  data->meta_delete = NULL;

  status = 0;
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if ((strcasecmp("Host", child->key) == 0) ||
        (strcasecmp("Hostname", child->key) == 0))
      status = ts_config_add_string(&data->host, child,
                                    /* may be empty = */ 0);
    else if (strcasecmp("Plugin", child->key) == 0)
      status = ts_config_add_string(&data->plugin, child,
                                    /* may be empty = */ 0);
    else if (strcasecmp("PluginInstance", child->key) == 0)
      status = ts_config_add_string(&data->plugin_instance, child,
                                    /* may be empty = */ 1);
#if 0
    else if (strcasecmp ("Type", child->key) == 0)
      status = ts_config_add_string (&data->type, child,
          /* may be empty = */ 0);
#endif
    else if (strcasecmp("TypeInstance", child->key) == 0)
      status = ts_config_add_string(&data->type_instance, child,
                                    /* may be empty = */ 1);
    else if (strcasecmp("MetaData", child->key) == 0)
      status = ts_config_add_meta(&data->meta, child,
                                  /* may be empty = */ 1);
    else if (strcasecmp("DeleteMetaData", child->key) == 0)
      status = ts_config_add_meta_delete(&data->meta_delete, child);
    else {
      ERROR("Target `set': The `%s' configuration option is not understood "
            "and will be ignored.",
            child->key);
      status = 0;
    }

    if (status != 0)
      break;
  }

  /* Additional sanity-checking */
  while (status == 0) {
    if ((data->host == NULL) && (data->plugin == NULL) &&
        (data->plugin_instance == NULL)
        /* && (data->type == NULL) */
        && (data->type_instance == NULL) && (data->meta == NULL) &&
        (data->meta_delete == NULL)) {
      ERROR("Target `set': You need to set at least one of `Host', "
            "`Plugin', `PluginInstance', `TypeInstance', "
            "`MetaData', or `DeleteMetaData'.");
      status = -1;
    }

    if (data->meta != NULL) {
      /* If data->meta_delete is NULL, this loop is a no-op. */
      for (ts_key_list_t *l = data->meta_delete; l != NULL; l = l->next) {
        if (meta_data_type(data->meta, l->key) != 0) {
          /* MetaData and DeleteMetaData for the same key. */
          ERROR("Target `set': Can only have one of `MetaData' or "
                "`DeleteMetaData' for any given key.");
          status = -1;
        }
      }
    }

    break;
  }

  if (status != 0) {
    ts_destroy((void *)&data);
    return status;
  }

  *user_data = data;
  return 0;
}
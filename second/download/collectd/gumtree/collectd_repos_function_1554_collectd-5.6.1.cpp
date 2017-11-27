static int tr_create (const oconfig_item_t *ci, void **user_data) /* {{{ */
{
  tr_data_t *data;
  int status;

  data = calloc (1, sizeof (*data));
  if (data == NULL)
  {
    ERROR ("tr_create: calloc failed.");
    return (-ENOMEM);
  }

  data->host = NULL;
  data->plugin = NULL;
  data->plugin_instance = NULL;
  /* data->type = NULL; */
  data->type_instance = NULL;

  status = 0;
  for (int i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *child = ci->children + i;

    if ((strcasecmp ("Host", child->key) == 0)
        || (strcasecmp ("Hostname", child->key) == 0))
      status = tr_config_add_action (&data->host, child,
          /* may be empty = */ 0);
    else if (strcasecmp ("Plugin", child->key) == 0)
      status = tr_config_add_action (&data->plugin, child,
          /* may be empty = */ 0);
    else if (strcasecmp ("PluginInstance", child->key) == 0)
      status = tr_config_add_action (&data->plugin_instance, child,
          /* may be empty = */ 1);
#if 0
    else if (strcasecmp ("Type", child->key) == 0)
      status = tr_config_add_action (&data->type, child,
          /* may be empty = */ 0);
#endif
    else if (strcasecmp ("TypeInstance", child->key) == 0)
      status = tr_config_add_action (&data->type_instance, child,
          /* may be empty = */ 1);
    else
    {
      ERROR ("Target `replace': The `%s' configuration option is not understood "
          "and will be ignored.", child->key);
      status = 0;
    }

    if (status != 0)
      break;
  }

  /* Additional sanity-checking */
  while (status == 0)
  {
    if ((data->host == NULL)
        && (data->plugin == NULL)
        && (data->plugin_instance == NULL)
        /* && (data->type == NULL) */
        && (data->type_instance == NULL))
    {
      ERROR ("Target `replace': You need to set at least one of `Host', "
          "`Plugin', `PluginInstance' or `TypeInstance'.");
      status = -1;
    }

    break;
  }

  if (status != 0)
  {
    tr_destroy ((void *) &data);
    return (status);
  }

  *user_data = data;
  return (0);
}
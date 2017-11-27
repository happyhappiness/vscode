static int mr_create(const oconfig_item_t *ci, void **user_data) /* {{{ */
{
  mr_match_t *m;
  int status;

  m = calloc(1, sizeof(*m));
  if (m == NULL) {
    log_err("mr_create: calloc failed.");
    return (-ENOMEM);
  }

  m->invert = 0;

  status = 0;
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if ((strcasecmp("Host", child->key) == 0) ||
        (strcasecmp("Hostname", child->key) == 0))
      status = mr_config_add_regex(&m->host, child);
    else if (strcasecmp("Plugin", child->key) == 0)
      status = mr_config_add_regex(&m->plugin, child);
    else if (strcasecmp("PluginInstance", child->key) == 0)
      status = mr_config_add_regex(&m->plugin_instance, child);
    else if (strcasecmp("Type", child->key) == 0)
      status = mr_config_add_regex(&m->type, child);
    else if (strcasecmp("TypeInstance", child->key) == 0)
      status = mr_config_add_regex(&m->type_instance, child);
    else if (strcasecmp("Invert", child->key) == 0)
      status = cf_util_get_boolean(child, &m->invert);
    else {
      log_err("The `%s' configuration option is not understood and "
              "will be ignored.",
              child->key);
      status = 0;
    }

    if (status != 0)
      break;
  }

  /* Additional sanity-checking */
  while (status == 0) {
    if ((m->host == NULL) && (m->plugin == NULL) &&
        (m->plugin_instance == NULL) && (m->type == NULL) &&
        (m->type_instance == NULL)) {
      log_err("No (valid) regular expressions have been configured. "
              "This match will be ignored.");
      status = -1;
    }

    break;
  }

  if (status != 0) {
    mr_free_match(m);
    return (status);
  }

  *user_data = m;
  return (0);
}
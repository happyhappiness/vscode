static int ut_config (oconfig_item_t *ci)
{ /* {{{ */
  int status = 0;
  int old_size = c_avl_size (threshold_tree);

  if (threshold_tree == NULL)
  {
    threshold_tree = c_avl_create ((int (*) (const void *, const void *)) strcmp);
    if (threshold_tree == NULL)
    {
      ERROR ("ut_config: c_avl_create failed.");
      return (-1);
    }
  }

  threshold_t th = {
    .warning_min = NAN,
    .warning_max = NAN,
    .failure_min = NAN,
    .failure_max = NAN,
    .flags = UT_FLAG_INTERESTING /* interesting by default */
  };

  for (int i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *option = ci->children + i;

    if (strcasecmp ("Type", option->key) == 0)
      status = ut_config_type (&th, option);
    else if (strcasecmp ("Plugin", option->key) == 0)
      status = ut_config_plugin (&th, option);
    else if (strcasecmp ("Host", option->key) == 0)
      status = ut_config_host (&th, option);
    else
    {
      WARNING ("threshold values: Option `%s' not allowed here.", option->key);
      status = -1;
    }

    if (status != 0)
      break;
  }

  /* register callbacks if this is the first time we see a valid config */
  if ((old_size == 0) && (c_avl_size (threshold_tree) > 0))
  {
    plugin_register_missing ("threshold", ut_missing,
        /* user data = */ NULL);
    plugin_register_write ("threshold", ut_check_threshold,
        /* user data = */ NULL);
  }

  return (status);
}
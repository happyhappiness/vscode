int ut_config (oconfig_item_t *ci)
{ /* {{{ */
  int i;
  int status = 0;

  threshold_t th;

  if (threshold_tree == NULL)
  {
    threshold_tree = c_avl_create ((void *) strcmp);
    if (threshold_tree == NULL)
    {
      ERROR ("ut_config: c_avl_create failed.");
      return (-1);
    }
  }

  memset (&th, '\0', sizeof (th));
  th.warning_min = NAN;
  th.warning_max = NAN;
  th.failure_min = NAN;
  th.failure_max = NAN;

  th.hits = 0;
  th.hysteresis = 0;
  th.flags = UT_FLAG_INTERESTING; /* interesting by default */
    
  for (i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *option = ci->children + i;
    status = 0;

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

  if (c_avl_size (threshold_tree) > 0) {
    plugin_register_missing ("threshold", ut_missing,
        /* user data = */ NULL);
    plugin_register_write ("threshold", ut_check_threshold,
        /* user data = */ NULL);
  }

  return (status);
}
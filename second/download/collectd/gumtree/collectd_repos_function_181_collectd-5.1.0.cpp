static int rc_config (oconfig_item_t *ci)
{
  int i;

  for (i = 0; i < ci->children_num; ++i) {
    const char *key = ci->children[i].key;
    const char *value = config_get_string (ci->children + i);

    if (value == NULL) /* config_get_strings prints error message */
      continue;

    if (strcasecmp ("DataDir", key) == 0)
    {
      if (datadir != NULL)
        free (datadir);
      datadir = strdup (value);
      if (datadir != NULL)
      {
        int len = strlen (datadir);
        while ((len > 0) && (datadir[len - 1] == '/'))
        {
          len--;
          datadir[len] = '\0';
        }
        if (len <= 0)
        {
          free (datadir);
          datadir = NULL;
        }
      }
    }
    else if (strcasecmp ("DaemonAddress", key) == 0)
    {
      sfree (daemon_address);
      daemon_address = strdup (value);
      if (daemon_address == NULL)
      {
        ERROR ("rrdcached plugin: strdup failed.");
        continue;
      }
    }
    else if (strcasecmp ("CreateFiles", key) == 0)
    {
      if (IS_FALSE (value))
        config_create_files = 0;
      else
        config_create_files = 1;
    }
    else if (strcasecmp ("CollectStatistics", key) == 0)
    {
      if (IS_FALSE (value))
        config_collect_stats = 0;
      else
        config_collect_stats = 1;
    }
    else
    {
      WARNING ("rrdcached plugin: Ignoring invalid option %s.", key);
      continue;
    }
  }

  if (daemon_address != NULL) {
    plugin_register_write ("rrdcached", rc_write, /* user_data = */ NULL);
    plugin_register_flush ("rrdcached", rc_flush, /* user_data = */ NULL);
  }
  return (0);
}
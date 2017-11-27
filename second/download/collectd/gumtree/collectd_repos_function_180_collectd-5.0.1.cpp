static int rc_config (const char *key, const char *value)
{
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
      return (1);
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
    return (-1);
  }
  return (0);
}
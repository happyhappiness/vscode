static int
chrony_config(const char *p_key, const char *p_value)
{
  assert(p_key);
  assert(p_value);

  /* Parse config variables */
  if (strcasecmp(p_key, CONFIG_KEY_HOST) == 0)
  {
    if (g_chrony_host != NULL)
      free(g_chrony_host);

    if ((g_chrony_host = strdup(p_value)) == NULL)
    {
      ERROR(PLUGIN_NAME ": Error duplicating host name");
      return CHRONY_RC_FAIL;
    }
  }
  else
  {
    if (strcasecmp(p_key, CONFIG_KEY_PORT) == 0)
    {
      if (g_chrony_port != NULL)
        free(g_chrony_port);

      if ((g_chrony_port = strdup(p_value)) == NULL)
      {
        ERROR(PLUGIN_NAME ": Error duplicating port name");
        return CHRONY_RC_FAIL;
      }
    }
    else
    {
      if (strcasecmp(p_key, CONFIG_KEY_TIMEOUT) == 0)
      {
        time_t tosec = strtol(p_value, NULL, 0);
        g_chrony_timeout = tosec;
      }
      else
      {
        WARNING(PLUGIN_NAME ": Unknown configuration variable: %s %s", p_key, p_value);
        return CHRONY_RC_FAIL;
      }
    }
  }
  /* XXX: We could set g_chrony_plugin_instance here to "g_chrony_host-g_chrony_port", but as multiple instances aren't yet supported, we skip this for now */

  return CHRONY_RC_OK;
}
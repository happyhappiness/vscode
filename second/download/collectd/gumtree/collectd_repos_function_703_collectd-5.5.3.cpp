static int cow_load_config (const char *key, const char *value)
{
  if (sensor_list == NULL)
    sensor_list = ignorelist_create (1);

  if (strcasecmp (key, "Sensor") == 0)
  {
    if (direct_list_insert (value))
    {
        DEBUG ("onewire plugin: Cannot add %s to direct_list_insert.", value);

        if (ignorelist_add (sensor_list, value))
        {
            ERROR ("onewire plugin: Cannot add value to ignorelist.");
            return (1);
        }
    }
    else
    {
        DEBUG ("onewire plugin: %s is a direct access", value);
        direct_access = 1;
    }
  }
  else if (strcasecmp (key, "IgnoreSelected") == 0)
  {
    ignorelist_set_invert (sensor_list, 1);
    if (IS_TRUE (value))
      ignorelist_set_invert (sensor_list, 0);
  }
  else if (strcasecmp (key, "Device") == 0)
  {
    char *temp;
    temp = strdup (value);
    if (temp == NULL)
    {
      ERROR ("onewire plugin: strdup failed.");
      return (1);
    }
    sfree (device_g);
    device_g = temp;
  }
  else if (strcasecmp ("Interval", key) == 0)
  {
    double tmp;
    tmp = atof (value);
    if (tmp > 0.0)
      ow_interval = DOUBLE_TO_CDTIME_T (tmp);
    else
      ERROR ("onewire plugin: Invalid `Interval' setting: %s", value);
  }
  else
  {
    return (-1);
  }

  return (0);
}
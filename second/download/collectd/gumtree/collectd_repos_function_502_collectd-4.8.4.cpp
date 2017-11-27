static int cow_load_config (const char *key, const char *value)
{
  if (sensor_list == NULL)
    sensor_list = ignorelist_create (1);

  if (strcasecmp (key, "Sensor") == 0)
  {
    if (ignorelist_add (sensor_list, value))
    {
      ERROR ("sensors plugin: "
          "Cannot add value to ignorelist.");
      return (1);
    }
  }
  else if (strcasecmp (key, "IgnoreSelected") == 0)
  {
    ignorelist_set_invert (sensor_list, 1);
    if ((strcasecmp (value, "True") == 0)
        || (strcasecmp (value, "Yes") == 0)
        || (strcasecmp (value, "On") == 0))
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
    int tmp;
    tmp = atoi (value);
    if (tmp > 0)
      ow_interval = tmp;
    else
      ERROR ("onewire plugin: Invalid `Interval' setting: %s", value);
  }
  else
  {
    return (-1);
  }

  return (0);
}
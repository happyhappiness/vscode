static int disk_config (const char *key, const char *value)
{
  if (ignorelist == NULL)
    ignorelist = ignorelist_create (/* invert = */ 1);
  if (ignorelist == NULL)
    return (1);

  if (strcasecmp ("Disk", key) == 0)
  {
    ignorelist_add (ignorelist, value);
  }
  else if (strcasecmp ("IgnoreSelected", key) == 0)
  {
    int invert = 1;
    if (IS_TRUE (value))
      invert = 0;
    ignorelist_set_invert (ignorelist, invert);
  }
  else if (strcasecmp ("UseBSDName", key) == 0)
  {
#if HAVE_IOKIT_IOKITLIB_H
    use_bsd_name = IS_TRUE (value) ? 1 : 0;
#else
    WARNING ("disk plugin: The \"UseBSDName\" option is only supported "
        "on Mach / Mac OS X and will be ignored.");
#endif
  }
  else if (strcasecmp ("UdevNameAttr", key) == 0)
  {
#if HAVE_LIBUDEV
    if (conf_udev_name_attr != NULL)
    {
      free (conf_udev_name_attr);
      conf_udev_name_attr = NULL;
    }
    if ((conf_udev_name_attr = strdup (value)) == NULL)
      return (1);
#else
    WARNING ("disk plugin: The \"UdevNameAttr\" option is only supported "
        "if collectd is built with libudev support");
#endif
  }
  else
  {
    return (-1);
  }

  return (0);
}
static int set_option (notification_t *n, const char *option, const char *value)
{
  if ((n == NULL) || (option == NULL) || (value == NULL))
    return (-1);

  DEBUG ("utils_cmd_putnotif: set_option (option = %s, value = %s);",
      option, value);

  /* Add a meta option in the form: <type>:<key> */
  if (option[0] != '\0' && option[1] == ':') {
    /* Refuse empty key */
    if (option[2] == '\0')
      return (1);

    if (option[0] == 's')
      return plugin_notification_meta_add_string (n, option + 2, value);
    else
      return (1);
  }

  if (strcasecmp ("severity", option) == 0)
    return (set_option_severity (n, value));
  else if (strcasecmp ("time", option) == 0)
    return (set_option_time (n, value));
  else if (strcasecmp ("message", option) == 0)
    sstrncpy (n->message, value, sizeof (n->message));
  else if (strcasecmp ("host", option) == 0)
    sstrncpy (n->host, value, sizeof (n->host));
  else if (strcasecmp ("plugin", option) == 0)
    sstrncpy (n->plugin, value, sizeof (n->plugin));
  else if (strcasecmp ("plugin_instance", option) == 0)
    sstrncpy (n->plugin_instance, value, sizeof (n->plugin_instance));
  else if (strcasecmp ("type", option) == 0)
    sstrncpy (n->type, value, sizeof (n->type));
  else if (strcasecmp ("type_instance", option) == 0)
    sstrncpy (n->type_instance, value, sizeof (n->type_instance));
  else
    return (1);

  return (0);
}
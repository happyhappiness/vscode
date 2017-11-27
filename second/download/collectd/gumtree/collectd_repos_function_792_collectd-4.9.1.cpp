static int tn_create (const oconfig_item_t *ci, void **user_data) /* {{{ */
{
  tn_data_t *data;
  int status;
  int i;

  data = (tn_data_t *) malloc (sizeof (*data));
  if (data == NULL)
  {
    ERROR ("tn_create: malloc failed.");
    return (-ENOMEM);
  }
  memset (data, 0, sizeof (*data));

  data->message = NULL;
  data->severity = 0;

  status = 0;
  for (i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp ("Message", child->key) == 0)
      status = tn_config_add_string (&data->message, child);
    else if (strcasecmp ("Severity", child->key) == 0)
      status = tn_config_add_severity (data, child);
    else
    {
      ERROR ("Target `notification': The `%s' configuration option is not understood "
          "and will be ignored.", child->key);
      status = 0;
    }

    if (status != 0)
      break;
  }

  /* Additional sanity-checking */
  while (status == 0)
  {
    if ((data->severity != NOTIF_FAILURE)
        && (data->severity != NOTIF_WARNING)
        && (data->severity != NOTIF_OKAY))
    {
      DEBUG ("Target `notification': Setting "
          "the default severity `WARNING'.");
      data->severity = NOTIF_WARNING;
    }

    if (data->message == NULL)
    {
      ERROR ("Target `notification': No `Message' option has been specified. "
          "Without it, the `Notification' target is useless.");
      status = -1;
    }

    break;
  }

  if (status != 0)
  {
    tn_destroy ((void *) data);
    return (status);
  }

  *user_data = data;
  return (0);
}
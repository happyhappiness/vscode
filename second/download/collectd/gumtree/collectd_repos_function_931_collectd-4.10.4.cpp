static int set_option_severity (notification_t *n, const char *value)
{
  if (strcasecmp (value, "Failure") == 0)
    n->severity = NOTIF_FAILURE;
  else if (strcasecmp (value, "Warning") == 0)
    n->severity = NOTIF_WARNING;
  else if (strcasecmp (value, "Okay") == 0)
    n->severity = NOTIF_OKAY;
  else
    return (-1);

  return (0);
}
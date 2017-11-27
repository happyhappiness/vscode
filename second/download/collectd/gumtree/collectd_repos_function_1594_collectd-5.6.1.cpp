static int statsd_parse_line (char *buffer) /* {{{ */
{
  char *name = buffer;
  char *value;
  char *type;
  char *extra;

  type = strchr (name, '|');
  if (type == NULL)
    return (-1);
  *type = 0;
  type++;

  value = strrchr (name, ':');
  if (value == NULL)
    return (-1);
  *value = 0;
  value++;

  extra = strchr (type, '|');
  if (extra != NULL)
  {
    *extra = 0;
    extra++;
  }

  if (strcmp ("c", type) == 0)
    return (statsd_handle_counter (name, value, extra));
  else if (strcmp ("ms", type) == 0)
    return (statsd_handle_timer (name, value, extra));

  /* extra is only valid for counters and timers */
  if (extra != NULL)
    return (-1);

  if (strcmp ("g", type) == 0)
    return (statsd_handle_gauge (name, value));
  else if (strcmp ("s", type) == 0)
    return (statsd_handle_set (name, value));
  else
    return (-1);
}
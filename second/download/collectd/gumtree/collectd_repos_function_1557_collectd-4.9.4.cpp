int plugin_notification_meta_add_string (notification_t *n,
    const char *name,
    const char *value)
{
  return (plugin_notification_meta_add (n, name, NM_TYPE_STRING, value));
}
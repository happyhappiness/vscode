int plugin_notification_meta_add_boolean (notification_t *n,
    const char *name,
    bool value)
{
  return (plugin_notification_meta_add (n, name, NM_TYPE_BOOLEAN, &value));
}
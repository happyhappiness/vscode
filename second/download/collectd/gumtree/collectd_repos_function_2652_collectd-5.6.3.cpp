int plugin_notification_meta_add_boolean(notification_t *n, const char *name,
                                         _Bool value) {
  return (plugin_notification_meta_add(n, name, NM_TYPE_BOOLEAN, &value));
}
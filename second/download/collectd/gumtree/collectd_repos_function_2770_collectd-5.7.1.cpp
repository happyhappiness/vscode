int plugin_notification_meta_add_double(notification_t *n, const char *name,
                                        double value) {
  return (plugin_notification_meta_add(n, name, NM_TYPE_DOUBLE, &value));
}
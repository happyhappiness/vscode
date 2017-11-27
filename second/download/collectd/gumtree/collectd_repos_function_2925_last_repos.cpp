int plugin_notification_meta_add_signed_int(notification_t *n, const char *name,
                                            int64_t value) {
  return plugin_notification_meta_add(n, name, NM_TYPE_SIGNED_INT, &value);
}
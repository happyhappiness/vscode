int plugin_notification_meta_add_unsigned_int(notification_t *n,
                                              const char *name,
                                              uint64_t value) {
  return plugin_notification_meta_add(n, name, NM_TYPE_UNSIGNED_INT, &value);
}
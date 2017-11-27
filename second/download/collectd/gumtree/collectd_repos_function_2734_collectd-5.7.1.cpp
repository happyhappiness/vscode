int plugin_register_notification(const char *name,
                                 plugin_notification_cb callback,
                                 user_data_t const *ud) {
  return (
      create_register_callback(&list_notification, name, (void *)callback, ud));
}
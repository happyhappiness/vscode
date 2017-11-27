int plugin_register_missing(const char *name, plugin_missing_cb callback,
                            user_data_t const *ud) {
  return create_register_callback(&list_missing, name, (void *)callback, ud);
}
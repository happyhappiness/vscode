int plugin_register_write(const char *name, plugin_write_cb callback,
                          user_data_t const *ud) {
  return (create_register_callback(&list_write, name, (void *)callback, ud));
}
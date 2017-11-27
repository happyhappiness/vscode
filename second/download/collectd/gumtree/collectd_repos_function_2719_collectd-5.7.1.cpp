int plugin_register_init(const char *name, int (*callback)(void)) {
  return (create_register_callback(&list_init, name, (void *)callback,
                                   /* user_data = */ NULL));
}
int plugin_register_complex_read(const char *group, const char *name,
                                 int (*callback)(user_data_t *),
                                 cdtime_t interval,
                                 user_data_t const *user_data) {
  return ENOTSUP;
}
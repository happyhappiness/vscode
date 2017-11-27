int plugin_register_shutdown(const char *name, int (*callback)(void)) {
  return ENOTSUP;
}

int plugin_dispatch_values(value_list_t const *vl) { return ENOTSUP; }

void plugin_log(int level, char const *format, ...) {
  char buffer[1024];
  va_list ap;

  va_start(ap, format);
  vsnprintf(buffer, sizeof(buffer), format, ap);

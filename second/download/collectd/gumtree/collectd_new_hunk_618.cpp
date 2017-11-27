#if HAVE_LIBKSTAT
kstat_ctl_t *kc = NULL;
#endif /* HAVE_LIBKSTAT */

char hostname_g[] = "example.com";

int plugin_register_complex_config(const char *type,
                                   int (*callback)(oconfig_item_t *)) {
  return ENOTSUP;
}

int plugin_register_init(const char *name, plugin_init_cb callback) {
  return ENOTSUP;
}

int plugin_register_read(const char *name, int (*callback)(void)) {
  return ENOTSUP;
}

int plugin_register_shutdown(const char *name, int (*callback)(void)) {
  return ENOTSUP;
}

int plugin_dispatch_values(value_list_t const *vl) { return ENOTSUP; }

void plugin_log(int level, char const *format, ...) {
  char buffer[1024];
  va_list ap;

  va_start(ap, format);
  vsnprintf(buffer, sizeof(buffer), format, ap);
  va_end(ap);

  printf("plugin_log (%i, \"%s\");\n", level, buffer);
}

cdtime_t plugin_get_interval(void) { return TIME_T_TO_CDTIME_T(10); }

/* vim: set sw=2 sts=2 et : */

static void submit_gauge(const char *type, const char *type_instance, gauge_t g,
                         apache_t *st) {
  submit_value(type, type_instance, (value_t){.gauge = g}, st);
}
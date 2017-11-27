static void za_submit_gauge(const char *type, const char *type_instance,
                            gauge_t value) {
  za_submit(type, type_instance, &(value_t){.gauge = value}, 1);
}
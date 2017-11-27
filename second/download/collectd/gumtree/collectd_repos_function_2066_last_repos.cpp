static void submit_gauge(const char *dev, const char *type, const char *ti1,
                         const char *ti2, gauge_t value) {
  submit(dev, type, ti1, ti2, &(value_t){.gauge = value}, 1);
}
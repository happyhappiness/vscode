static void submit_gauge(const char *dev, const char *type, const char *ti1,
                         const char *ti2, gauge_t val) {
  value_t item;
  item.gauge = val;
  submit(dev, type, ti1, ti2, &item, 1);
}
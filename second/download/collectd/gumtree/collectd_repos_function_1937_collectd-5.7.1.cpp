static void submit_derive(const char *dev, const char *type, const char *ti1,
                          const char *ti2, derive_t value) {
  submit(dev, type, ti1, ti2, &(value_t){.derive = value}, 1);
}
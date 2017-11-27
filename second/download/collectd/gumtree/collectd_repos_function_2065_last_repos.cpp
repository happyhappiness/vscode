static void submit_derive2(const char *dev, const char *type, const char *ti1,
                           const char *ti2, derive_t val1, derive_t val2) {
  value_t values[] = {
      {.derive = val1}, {.derive = val2},
  };

  submit(dev, type, ti1, ti2, values, STATIC_ARRAY_SIZE(values));
}
static void submit_derive2(const char *type, derive_t v0, derive_t v1,
                           virDomainPtr dom, const char *devname) {
  value_t values[] = {
      {.derive = v0}, {.derive = v1},
  };

  submit(dom, type, devname, values, STATIC_ARRAY_SIZE(values));
}
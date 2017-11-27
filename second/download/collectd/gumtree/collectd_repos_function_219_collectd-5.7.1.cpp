static void cpu_submit(unsigned long long value, virDomainPtr dom,
                       const char *type) {
  submit(dom, type, NULL, &(value_t){.derive = (derive_t)value}, 1);
}
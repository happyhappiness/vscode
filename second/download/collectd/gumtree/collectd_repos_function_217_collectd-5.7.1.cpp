static void memory_submit(gauge_t value, virDomainPtr dom) {
  submit(dom, "memory", "total", &(value_t){.gauge = value}, 1);
}
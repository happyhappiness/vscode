static void memory_submit(virDomainPtr dom, gauge_t value) {
  submit(dom, "memory", "total", &(value_t){.gauge = value}, 1);
}
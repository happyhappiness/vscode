static void memory_stats_submit(gauge_t value, virDomainPtr dom,
                                int tag_index) {
  static const char *tags[] = {"swap_in",        "swap_out", "major_fault",
                               "minor_fault",    "unused",   "available",
                               "actual_balloon", "rss"};

  if ((tag_index < 0) || (tag_index >= STATIC_ARRAY_SIZE(tags))) {
    ERROR("virt plugin: Array index out of bounds: tag_index = %d", tag_index);
    return;
  }

  submit(dom, "memory", tags[tag_index], &(value_t){.gauge = value}, 1);
}
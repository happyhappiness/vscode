static int submit_two_gauge(const char *host, const char *plugin_inst, /* {{{ */
                            const char *type, const char *type_inst,
                            gauge_t val0, gauge_t val1, cdtime_t timestamp,
                            cdtime_t interval) {
  value_t values[] = {
      {.gauge = val0}, {.gauge = val1},
  };

  return (submit_values(host, plugin_inst, type, type_inst, values,
                        STATIC_ARRAY_SIZE(values), timestamp, interval));
}
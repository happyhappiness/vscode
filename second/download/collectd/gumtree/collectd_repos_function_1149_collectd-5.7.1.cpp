static int submit_double(const char *host, const char *plugin_inst, /* {{{ */
                         const char *type, const char *type_inst, double d,
                         cdtime_t timestamp, cdtime_t interval) {
  return (submit_values(host, plugin_inst, type, type_inst,
                        &(value_t){.gauge = d}, 1, timestamp, interval));
}
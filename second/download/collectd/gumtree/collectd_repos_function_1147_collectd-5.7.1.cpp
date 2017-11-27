static int submit_derive(const char *host, const char *plugin_inst, /* {{{ */
                         const char *type, const char *type_inst,
                         derive_t counter, cdtime_t timestamp,
                         cdtime_t interval) {
  return (submit_values(host, plugin_inst, type, type_inst,
                        &(value_t){.derive = counter}, 1, timestamp, interval));
}
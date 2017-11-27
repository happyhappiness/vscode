static int varnish_submit_gauge(const char *plugin_instance, /* {{{ */
                                const char *category, const char *type,
                                const char *type_instance,
                                uint64_t gauge_value) {
  return (varnish_submit(plugin_instance, category, type, type_instance,
                         (value_t){.gauge = (gauge_t)gauge_value}));
}
static void battery_submit(char const *plugin_instance, /* {{{ */
                           char const *type, gauge_t value) {
  battery_submit2(plugin_instance, type, NULL, value);
}
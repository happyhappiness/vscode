static void cldap_submit_gauge(const char *type,
                               const char *type_instance, /* {{{ */
                               gauge_t g, cldap_t *st) {
  cldap_submit_value(type, type_instance, (value_t){.gauge = g}, st);
}
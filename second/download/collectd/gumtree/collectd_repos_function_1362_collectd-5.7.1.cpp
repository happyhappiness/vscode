static void cldap_submit_derive(const char *type,
                                const char *type_instance, /* {{{ */
                                derive_t d, cldap_t *st) {
  cldap_submit_value(type, type_instance, (value_t){.derive = d}, st);
}
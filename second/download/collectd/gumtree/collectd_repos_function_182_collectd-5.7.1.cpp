static void submit_derive(const char *type, const char *type_instance,
                          derive_t d, apache_t *st) {
  submit_value(type, type_instance, (value_t){.derive = d}, st);
}
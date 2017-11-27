static void submit(virDomainPtr dom, char const *type,
                   char const *type_instance, value_t *values,
                   size_t values_len) {
  value_list_t vl = VALUE_LIST_INIT;
  init_value_list(&vl, dom);

  vl.values = values;
  vl.values_len = values_len;

  sstrncpy(vl.type, type, sizeof(vl.type));
  if (type_instance != NULL)
    sstrncpy(vl.type_instance, type_instance, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}
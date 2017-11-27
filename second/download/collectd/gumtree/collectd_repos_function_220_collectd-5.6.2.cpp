static void submit_derive2(const char *type, derive_t v0, derive_t v1,
                           virDomainPtr dom, const char *devname) {
  value_t values[2];
  value_list_t vl = VALUE_LIST_INIT;

  init_value_list(&vl, dom);

  values[0].derive = v0;
  values[1].derive = v1;
  vl.values = values;
  vl.values_len = 2;

  sstrncpy(vl.type, type, sizeof(vl.type));
  sstrncpy(vl.type_instance, devname, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}
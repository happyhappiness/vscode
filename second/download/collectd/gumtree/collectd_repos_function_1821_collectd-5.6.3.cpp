static void submit(const char *dev, const char *type, const char *ti1,
                   const char *ti2, value_t *val, int len) {
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = val;
  vl.values_len = len;
  sstrncpy(vl.host, hostname_g, sizeof(vl.host));
  sstrncpy(vl.plugin, "madwifi", sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, dev, sizeof(vl.plugin_instance));
  sstrncpy(vl.type, type, sizeof(vl.type));

  if ((ti1 != NULL) && (ti2 != NULL))
    ssnprintf(vl.type_instance, sizeof(vl.type_instance), "%s-%s", ti1, ti2);
  else if ((ti1 != NULL) && (ti2 == NULL))
    sstrncpy(vl.type_instance, ti1, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}
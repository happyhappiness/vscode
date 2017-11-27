static void compression_submit(const char *pinst, const char *tinst,
                               derive_t uncompressed, derive_t compressed) {
  value_list_t vl = VALUE_LIST_INIT;
  value_t values[] = {
      {.derive = uncompressed}, {.derive = compressed},
  };

  vl.values = values;
  vl.values_len = STATIC_ARRAY_SIZE(values);
  sstrncpy(vl.plugin, "openvpn", sizeof(vl.plugin));
  if (pinst != NULL)
    sstrncpy(vl.plugin_instance, pinst, sizeof(vl.plugin_instance));
  sstrncpy(vl.type, "compression", sizeof(vl.type));
  if (tinst != NULL)
    sstrncpy(vl.type_instance, tinst, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}
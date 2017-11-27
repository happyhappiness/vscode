static void iostats_submit(const char *pinst, const char *tinst, derive_t rx,
                           derive_t tx) {
  value_list_t vl = VALUE_LIST_INIT;
  value_t values[] = {
      {.derive = rx}, {.derive = tx},
  };

  /* NOTE ON THE NEW NAMING SCHEMA:
   *       using plugin_instance to identify each vpn config (and
   *       status) file; using type_instance to identify the endpoint
   *       host when in multimode, traffic or overhead when in single.
   */

  vl.values = values;
  vl.values_len = STATIC_ARRAY_SIZE(values);
  sstrncpy(vl.plugin, "openvpn", sizeof(vl.plugin));
  if (pinst != NULL)
    sstrncpy(vl.plugin_instance, pinst, sizeof(vl.plugin_instance));
  sstrncpy(vl.type, "if_octets", sizeof(vl.type));
  if (tinst != NULL)
    sstrncpy(vl.type_instance, tinst, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}
static void chrony_push_data(const char *p_type, const char *p_type_inst,
                             double p_value) {
  value_t values[1];
  value_list_t vl = VALUE_LIST_INIT;

  values[0].gauge =
      p_value; /* TODO: Check type??? (counter, gauge, derive, absolute) */

  vl.values = values;
  vl.values_len = 1;

  /* XXX: Shall g_chrony_host/g_chrony_port be reflected in the plugin's output?
   */
  /* hostname_g is set in daemon/collectd.c (from config, via gethostname or by
   * resolving localhost) */
  /* defined as: char hostname_g[DATA_MAX_NAME_LEN]; (never NULL) */
  sstrncpy(vl.host, hostname_g, sizeof(vl.host));
  sstrncpy(vl.plugin, PLUGIN_NAME_SHORT, sizeof(vl.plugin));
  if (g_chrony_plugin_instance != NULL) {
    sstrncpy(vl.plugin_instance, g_chrony_plugin_instance,
             sizeof(vl.plugin_instance));
  }
  if (p_type != NULL)
    sstrncpy(vl.type, p_type, sizeof(vl.type));

  if (p_type_inst != NULL)
    sstrncpy(vl.type_instance, p_type_inst, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}
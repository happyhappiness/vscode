static void chrony_push_data(const char *p_type, const char *p_type_inst,
                             double p_value) {
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &(value_t){.gauge = p_value};
  vl.values_len = 1;

  /* XXX: Shall g_chrony_host/g_chrony_port be reflected in the plugin's output?
   */
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
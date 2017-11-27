static void mic_submit_memory_use(int micnumber, const char *type_instance,
                                  U32 value) {
  value_list_t vl = VALUE_LIST_INIT;

  /* MicAccessAPI reports KB's of memory, adjust for this */
  DEBUG("mic plugin: Memory Value Report; %u %lf", value,
        ((gauge_t)value) * 1024.0);

  vl.values = &(value_t){.gauge = ((gauge_t)value) * 1024.0};
  vl.values_len = 1;

  strncpy(vl.plugin, "mic", sizeof(vl.plugin));
  ssnprintf(vl.plugin_instance, sizeof(vl.plugin_instance), "%i", micnumber);
  strncpy(vl.type, "memory", sizeof(vl.type));
  strncpy(vl.type_instance, type_instance, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}
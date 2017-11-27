static void synproxy_submit(value_t *results) {
  value_list_t vl = VALUE_LIST_INIT;

  /* 1st column (entries) is hardcoded to 0 in kernel code */
  for (size_t n = 1; n < SYNPROXY_FIELDS; n++) {
    vl.values = &results[n];
    vl.values_len = 1;

    sstrncpy(vl.plugin, "synproxy", sizeof(vl.plugin));
    sstrncpy(vl.type, column_types[n], sizeof(vl.type));
    sstrncpy(vl.type_instance, column_names[n], sizeof(vl.type_instance));

    plugin_dispatch_values(&vl);
  }
}
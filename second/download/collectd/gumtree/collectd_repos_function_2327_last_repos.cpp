int curl_stats_dispatch(curl_stats_t *s, CURL *curl, const char *hostname,
                        const char *plugin, const char *plugin_instance) {
  value_list_t vl = VALUE_LIST_INIT;

  if (s == NULL)
    return 0;
  if ((curl == NULL) || (plugin == NULL)) {
    ERROR("curl stats: dispatch() called with missing arguments "
          "(curl=%p; plugin=%s)",
          curl, plugin == NULL ? "<NULL>" : plugin);
    return -1;
  }

  if (hostname != NULL)
    sstrncpy(vl.host, hostname, sizeof(vl.host));
  sstrncpy(vl.plugin, plugin, sizeof(vl.plugin));
  if (plugin_instance != NULL)
    sstrncpy(vl.plugin_instance, plugin_instance, sizeof(vl.plugin_instance));

  for (size_t field = 0; field < STATIC_ARRAY_SIZE(field_specs); ++field) {
    int status;

    if (!field_enabled(s, field_specs[field].offset))
      continue;

    sstrncpy(vl.type, field_specs[field].type, sizeof(vl.type));
    sstrncpy(vl.type_instance, field_specs[field].name,
             sizeof(vl.type_instance));

    vl.values = NULL;
    vl.values_len = 0;
    status = field_specs[field].dispatcher(curl, field_specs[field].info, &vl);
    if (status < 0)
      return status;
  }

  return 0;
}
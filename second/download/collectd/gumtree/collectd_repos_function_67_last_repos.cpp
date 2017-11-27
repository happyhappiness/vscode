static void init_value_list(value_list_t *vl, virDomainPtr dom) {
  int n;
  const char *name;
  char uuid[VIR_UUID_STRING_BUFLEN];

  sstrncpy(vl->plugin, PLUGIN_NAME, sizeof(vl->plugin));

  vl->host[0] = '\0';

  /* Construct the hostname field according to HostnameFormat. */
  for (int i = 0; i < HF_MAX_FIELDS; ++i) {
    if (hostname_format[i] == hf_none)
      continue;

    n = DATA_MAX_NAME_LEN - strlen(vl->host) - 2;

    if (i > 0 && n >= 1) {
      strncat(vl->host, ":", 1);
      n--;
    }

    switch (hostname_format[i]) {
    case hf_none:
      break;
    case hf_hostname:
      strncat(vl->host, hostname_g, n);
      break;
    case hf_name:
      name = virDomainGetName(dom);
      if (name)
        strncat(vl->host, name, n);
      break;
    case hf_uuid:
      if (virDomainGetUUIDString(dom, uuid) == 0)
        strncat(vl->host, uuid, n);
      break;
    }
  }

  vl->host[sizeof(vl->host) - 1] = '\0';

  /* Construct the plugin instance field according to PluginInstanceFormat. */
  for (int i = 0; i < PLGINST_MAX_FIELDS; ++i) {
    if (plugin_instance_format[i] == plginst_none)
      continue;

    n = sizeof(vl->plugin_instance) - strlen(vl->plugin_instance) - 2;

    if (i > 0 && n >= 1) {
      strncat(vl->plugin_instance, ":", 1);
      n--;
    }

    switch (plugin_instance_format[i]) {
    case plginst_none:
      break;
    case plginst_name:
      name = virDomainGetName(dom);
      if (name)
        strncat(vl->plugin_instance, name, n);
      break;
    case plginst_uuid:
      if (virDomainGetUUIDString(dom, uuid) == 0)
        strncat(vl->plugin_instance, uuid, n);
      break;
    }
  }

  vl->plugin_instance[sizeof(vl->plugin_instance) - 1] = '\0';

}
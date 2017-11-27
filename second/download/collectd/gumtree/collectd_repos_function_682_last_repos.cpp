static int ps_config(oconfig_item_t *ci) {
#if KERNEL_LINUX
  const size_t max_procname_len = 15;
#elif KERNEL_SOLARIS || KERNEL_FREEBSD
  const size_t max_procname_len = MAXCOMLEN - 1;
#endif

  procstat_t *ps;

  for (int i = 0; i < ci->children_num; ++i) {
    oconfig_item_t *c = ci->children + i;

    if (strcasecmp(c->key, "Process") == 0) {
      if ((c->values_num != 1) || (OCONFIG_TYPE_STRING != c->values[0].type)) {
        ERROR("processes plugin: `Process' expects exactly "
              "one string argument (got %i).",
              c->values_num);
        continue;
      }

#if KERNEL_LINUX || KERNEL_SOLARIS || KERNEL_FREEBSD
      if (strlen(c->values[0].value.string) > max_procname_len) {
        WARNING("processes plugin: this platform has a %zu character limit "
                "to process names. The `Process \"%s\"' option will "
                "not work as expected.",
                max_procname_len, c->values[0].value.string);
      }
#endif

      ps = ps_list_register(c->values[0].value.string, NULL);

      if (c->children_num != 0 && ps != NULL)
        ps_tune_instance(c, ps);
    } else if (strcasecmp(c->key, "ProcessMatch") == 0) {
      if ((c->values_num != 2) || (OCONFIG_TYPE_STRING != c->values[0].type) ||
          (OCONFIG_TYPE_STRING != c->values[1].type)) {
        ERROR("processes plugin: `ProcessMatch' needs exactly "
              "two string arguments (got %i).",
              c->values_num);
        continue;
      }

      ps = ps_list_register(c->values[0].value.string,
                            c->values[1].value.string);

      if (c->children_num != 0 && ps != NULL)
        ps_tune_instance(c, ps);
    } else if (strcasecmp(c->key, "CollectContextSwitch") == 0) {
      cf_util_get_boolean(c, &report_ctx_switch);
    } else if (strcasecmp(c->key, "CollectFileDescriptor") == 0) {
      cf_util_get_boolean(c, &report_fd_num);
    } else if (strcasecmp(c->key, "CollectMemoryMaps") == 0) {
      cf_util_get_boolean(c, &report_maps_num);
    } else {
      ERROR("processes plugin: The `%s' configuration option is not "
            "understood and will be ignored.",
            c->key);
      continue;
    }
  }

  return 0;
}
static int mcelog_config(oconfig_item_t *ci) {
  int use_logfile = 0, use_memory = 0;
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;
    if (strcasecmp("McelogLogfile", child->key) == 0) {
      use_logfile = 1;
      if (use_memory) {
        ERROR(MCELOG_PLUGIN ": Invalid configuration option: \"%s\", Memory "
                            "option is already configured.",
              child->key);
        return -1;
      }
      if (cf_util_get_string_buffer(child, g_mcelog_config.logfile,
                                    sizeof(g_mcelog_config.logfile)) < 0) {
        ERROR(MCELOG_PLUGIN ": Invalid configuration option: \"%s\".",
              child->key);
        return -1;
      }
      memset(socket_adapter.unix_sock.sun_path, 0,
             sizeof(socket_adapter.unix_sock.sun_path));
    } else if (strcasecmp("Memory", child->key) == 0) {
      if (use_logfile) {
        ERROR(MCELOG_PLUGIN ": Invalid configuration option: \"%s\", Logfile "
                            "option is already configured.",
              child->key);
        return -1;
      }
      use_memory = 1;
      for (int j = 0; j < child->children_num; j++) {
        oconfig_item_t *mem_child = child->children + j;
        if (strcasecmp("McelogClientSocket", mem_child->key) == 0) {
          if (cf_util_get_string_buffer(
                  mem_child, socket_adapter.unix_sock.sun_path,
                  sizeof(socket_adapter.unix_sock.sun_path)) < 0) {
            ERROR(MCELOG_PLUGIN ": Invalid configuration option: \"%s\".",
                  mem_child->key);
            return -1;
          }
        } else if (strcasecmp("PersistentNotification", mem_child->key) == 0) {
          if (cf_util_get_boolean(mem_child, &g_mcelog_config.persist) < 0) {
            ERROR(MCELOG_PLUGIN ": Invalid configuration option: \"%s\".",
                  mem_child->key);
            return -1;
          }
        } else {
          ERROR(MCELOG_PLUGIN ": Invalid Memory configuration option: \"%s\".",
                mem_child->key);
          return -1;
        }
      }
      memset(g_mcelog_config.logfile, 0, sizeof(g_mcelog_config.logfile));
    } else {
      ERROR(MCELOG_PLUGIN ": Invalid configuration option: \"%s\".",
            child->key);
      return -1;
    }
  }

  if (!use_logfile && !use_memory)
    mcelog_apply_defaults = 1;

  return 0;
}
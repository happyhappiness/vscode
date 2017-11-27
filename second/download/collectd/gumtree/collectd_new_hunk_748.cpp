                       &type_instance, opts->identifier_default_host);
  if (status != 0) {
    DEBUG("cmd_handle_putval: Cannot parse identifier `%s'.", identifier_copy);
    cmd_error(CMD_PARSE_ERROR, err, "Cannot parse identifier `%s'.",
              identifier_copy);
    sfree(identifier_copy);
    return CMD_PARSE_ERROR;
  }

  if ((strlen(hostname) >= sizeof(vl.host)) ||
      (strlen(plugin) >= sizeof(vl.plugin)) ||
      ((plugin_instance != NULL) &&
       (strlen(plugin_instance) >= sizeof(vl.plugin_instance))) ||
      ((type_instance != NULL) &&
       (strlen(type_instance) >= sizeof(vl.type_instance)))) {
    cmd_error(CMD_PARSE_ERROR, err, "Identifier too long.");
    sfree(identifier_copy);
    return CMD_PARSE_ERROR;
  }

  sstrncpy(vl.host, hostname, sizeof(vl.host));
  sstrncpy(vl.plugin, plugin, sizeof(vl.plugin));
  sstrncpy(vl.type, type, sizeof(vl.type));
  if (plugin_instance != NULL)

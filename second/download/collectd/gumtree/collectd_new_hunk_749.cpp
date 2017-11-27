    sstrncpy(vl.type_instance, type_instance, sizeof(vl.type_instance));

  ds = plugin_get_ds(type);
  if (ds == NULL) {
    cmd_error(CMD_PARSE_ERROR, err, "1 Type `%s' isn't defined.", type);
    sfree(identifier_copy);
    return CMD_PARSE_ERROR;
  }

  hostname = NULL;
  plugin = NULL;
  plugin_instance = NULL;
  type = NULL;

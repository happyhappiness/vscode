  gauge_t *values;
  size_t values_num;

  const data_set_t *ds;

  if ((fh == NULL) || (buffer == NULL))
    return -1;

  DEBUG("utils_cmd_getval: cmd_handle_getval (fh = %p, buffer = %s);",
        (void *)fh, buffer);

  if ((status = cmd_parse(buffer, &cmd, NULL, &err)) != CMD_OK)
    return status;
  if (cmd.type != CMD_GETVAL) {
    cmd_error(CMD_UNKNOWN_COMMAND, &err, "Unexpected command: `%s'.",
              CMD_TO_STRING(cmd.type));
    cmd_destroy(&cmd);
    return CMD_UNKNOWN_COMMAND;
  }

  ds = plugin_get_ds(cmd.cmd.getval.identifier.type);
  if (ds == NULL) {
    DEBUG("cmd_handle_getval: plugin_get_ds (%s) == NULL;",
          cmd.cmd.getval.identifier.type);
    cmd_error(CMD_ERROR, &err, "Type `%s' is unknown.\n",
              cmd.cmd.getval.identifier.type);
    cmd_destroy(&cmd);
    return -1;
  }

  values = NULL;
  values_num = 0;
  status =
      uc_get_rate_by_name(cmd.cmd.getval.raw_identifier, &values, &values_num);
  if (status != 0) {
    cmd_error(CMD_ERROR, &err, "No such value.");
    cmd_destroy(&cmd);
    return CMD_ERROR;
  }

  if (ds->ds_num != values_num) {
    ERROR("ds[%s]->ds_num = %zu, "
          "but uc_get_rate_by_name returned %zu values.",
          ds->type, ds->ds_num, values_num);
    cmd_error(CMD_ERROR, &err, "Error reading value from cache.");
    sfree(values);
    cmd_destroy(&cmd);
    return CMD_ERROR;
  }

  print_to_socket(fh, "%zu Value%s found\n", values_num,
                  (values_num == 1) ? "" : "s");
  for (size_t i = 0; i < values_num; i++) {
    print_to_socket(fh, "%s=", ds->ds[i].name);

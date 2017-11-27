  int status;

  DEBUG("utils_cmd_putval: cmd_handle_putval (fh = %p, buffer = %s);",
        (void *)fh, buffer);

  if ((status = cmd_parse(buffer, &cmd, NULL, &err)) != CMD_OK)
    return status;
  if (cmd.type != CMD_PUTVAL) {
    cmd_error(CMD_UNKNOWN_COMMAND, &err, "Unexpected command: `%s'.",
              CMD_TO_STRING(cmd.type));
    cmd_destroy(&cmd);
    return CMD_UNKNOWN_COMMAND;
  }

  for (size_t i = 0; i < cmd.cmd.putval.vl_num; ++i)
    plugin_dispatch_values(&cmd.cmd.putval.vl[i]);

  if (fh != stdout)
    cmd_error(CMD_OK, &err, "Success: %i %s been dispatched.",
              (int)cmd.cmd.putval.vl_num,
              (cmd.cmd.putval.vl_num == 1) ? "value has" : "values have");

  cmd_destroy(&cmd);
  return CMD_OK;
} /* int cmd_handle_putval */

int cmd_create_putval(char *ret, size_t ret_len, /* {{{ */
                      const data_set_t *ds, const value_list_t *vl) {
  char buffer_ident[6 * DATA_MAX_NAME_LEN];
  char buffer_values[1024];
  int status;

  status = FORMAT_VL(buffer_ident, sizeof(buffer_ident), vl);
  if (status != 0)
    return status;
  escape_string(buffer_ident, sizeof(buffer_ident));

  status = format_values(buffer_values, sizeof(buffer_values), ds, vl,
                         /* store rates = */ 0);
  if (status != 0)
    return status;
  escape_string(buffer_values, sizeof(buffer_values));

  snprintf(ret, ret_len, "PUTVAL %s interval=%.3f %s", buffer_ident,
           (vl->interval > 0) ? CDTIME_T_TO_DOUBLE(vl->interval)
                              : CDTIME_T_TO_DOUBLE(plugin_get_interval()),
           buffer_values);

  return 0;
} /* }}} int cmd_create_putval */

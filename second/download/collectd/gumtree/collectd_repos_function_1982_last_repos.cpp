cmd_status_t cmd_handle_putval(FILE *fh, char *buffer) {
  cmd_error_handler_t err = {cmd_error_fh, fh};
  cmd_t cmd;

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
}
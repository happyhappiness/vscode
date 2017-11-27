cmd_status_t cmd_parsev(size_t argc, char **argv, cmd_t *ret_cmd,
                        const cmd_options_t *opts, cmd_error_handler_t *err) {
  char *command = NULL;
  cmd_status_t status;

  if ((argc < 1) || (argv == NULL) || (ret_cmd == NULL)) {
    errno = EINVAL;
    cmd_error(CMD_ERROR, err, "Missing command.");
    return CMD_ERROR;
  }

  if (opts == NULL)
    opts = &default_options;

  memset(ret_cmd, 0, sizeof(*ret_cmd));
  command = argv[0];
  if (strcasecmp("FLUSH", command) == 0) {
    ret_cmd->type = CMD_FLUSH;
    status =
        cmd_parse_flush(argc - 1, argv + 1, &ret_cmd->cmd.flush, opts, err);
  } else if (strcasecmp("GETVAL", command) == 0) {
    ret_cmd->type = CMD_GETVAL;
    status =
        cmd_parse_getval(argc - 1, argv + 1, &ret_cmd->cmd.getval, opts, err);
  } else if (strcasecmp("LISTVAL", command) == 0) {
    ret_cmd->type = CMD_LISTVAL;
    status =
        cmd_parse_listval(argc - 1, argv + 1, &ret_cmd->cmd.listval, opts, err);
  } else if (strcasecmp("PUTVAL", command) == 0) {
    ret_cmd->type = CMD_PUTVAL;
    status =
        cmd_parse_putval(argc - 1, argv + 1, &ret_cmd->cmd.putval, opts, err);
  } else {
    ret_cmd->type = CMD_UNKNOWN;
    cmd_error(CMD_UNKNOWN_COMMAND, err, "Unknown command `%s'.", command);
    return CMD_UNKNOWN_COMMAND;
  }

  if (status != CMD_OK)
    ret_cmd->type = CMD_UNKNOWN;
  return status;
}
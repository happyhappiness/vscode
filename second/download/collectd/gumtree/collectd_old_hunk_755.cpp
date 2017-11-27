    ret_cmd->type = CMD_PUTVAL;
    status =
        cmd_parse_putval(argc - 1, argv + 1, &ret_cmd->cmd.putval, opts, err);
  } else {
    ret_cmd->type = CMD_UNKNOWN;
    cmd_error(CMD_UNKNOWN_COMMAND, err, "Unknown command `%s'.", command);
    return (CMD_UNKNOWN_COMMAND);
  }

  if (status != CMD_OK)
    ret_cmd->type = CMD_UNKNOWN;
  return (status);
} /* cmd_status_t cmd_parsev */

cmd_status_t cmd_parse(char *buffer, cmd_t *ret_cmd, const cmd_options_t *opts,
                       cmd_error_handler_t *err) {
  char **fields = NULL;
  size_t fields_num = 0;

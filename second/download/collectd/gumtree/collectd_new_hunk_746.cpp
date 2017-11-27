  size_t number = 0;

  DEBUG("utils_cmd_listval: handle_listval (fh = %p, buffer = %s);", (void *)fh,
        buffer);

  if ((status = cmd_parse(buffer, &cmd, NULL, &err)) != CMD_OK)
    return status;
  if (cmd.type != CMD_LISTVAL) {
    cmd_error(CMD_UNKNOWN_COMMAND, &err, "Unexpected command: `%s'.",
              CMD_TO_STRING(cmd.type));
    free_everything_and_return(CMD_UNKNOWN_COMMAND);
  }


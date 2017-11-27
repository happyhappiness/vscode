
      if ((endptr == opt_value) || (errno != 0) ||
          (!isfinite(ret_flush->timeout))) {
        cmd_error(CMD_PARSE_ERROR, err,
                  "Invalid value for option `timeout': %s", opt_value);
        cmd_destroy_flush(ret_flush);
        return CMD_PARSE_ERROR;
      } else if (ret_flush->timeout < 0.0) {
        ret_flush->timeout = 0.0;
      }
    } else {
      cmd_error(CMD_PARSE_ERROR, err, "Cannot parse option `%s'.", opt_key);
      cmd_destroy_flush(ret_flush);
      return CMD_PARSE_ERROR;
    }
  }

  return CMD_OK;
} /* cmd_status_t cmd_parse_flush */

cmd_status_t cmd_handle_flush(FILE *fh, char *buffer) {
  cmd_error_handler_t err = {cmd_error_fh, fh};
  cmd_t cmd;

  int success = 0;
  int error = 0;
  int status;

  if ((fh == NULL) || (buffer == NULL))
    return -1;

  DEBUG("utils_cmd_flush: cmd_handle_flush (fh = %p, buffer = %s);", (void *)fh,
        buffer);

  if ((status = cmd_parse(buffer, &cmd, NULL, &err)) != CMD_OK)
    return status;
  if (cmd.type != CMD_FLUSH) {
    cmd_error(CMD_UNKNOWN_COMMAND, &err, "Unexpected command: `%s'.",
              CMD_TO_STRING(cmd.type));
    cmd_destroy(&cmd);
    return CMD_UNKNOWN_COMMAND;
  }

  for (size_t i = 0; (i == 0) || (i < cmd.cmd.flush.plugins_num); i++) {
    char *plugin = NULL;

    if (cmd.cmd.flush.plugins_num != 0)
      plugin = cmd.cmd.flush.plugins[i];

    for (size_t j = 0; (j == 0) || (j < cmd.cmd.flush.identifiers_num); j++) {
      char *identifier = NULL;
      char buf[1024];

      if (cmd.cmd.flush.identifiers_num != 0) {
        identifier_t *id = cmd.cmd.flush.identifiers + j;
        if (format_name(buf, sizeof(buf), id->host, id->plugin,
                        id->plugin_instance, id->type,
                        id->type_instance) != 0) {
          error++;
          continue;
        }
        identifier = buf;
      }

      if (plugin_flush(plugin, DOUBLE_TO_CDTIME_T(cmd.cmd.flush.timeout),
                       identifier) == 0)
        success++;
      else
        error++;
    }
  }

  cmd_error(CMD_OK, &err, "Done: %i successful, %i errors", success, error);

  cmd_destroy(&cmd);
  return 0;
#undef PRINT_TO_SOCK
} /* cmd_status_t cmd_handle_flush */

void cmd_destroy_flush(cmd_flush_t *flush) {
  if (flush == NULL)
    return;

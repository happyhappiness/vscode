#define print_to_socket(fh, ...)                                               \
  do {                                                                         \
    if (fprintf(fh, __VA_ARGS__) < 0) {                                        \
      char errbuf[1024];                                                       \
      WARNING("handle_listval: failed to write to socket #%i: %s", fileno(fh), \
              sstrerror(errno, errbuf, sizeof(errbuf)));                       \
      free_everything_and_return(CMD_ERROR);                                   \
    }                                                                          \
    fflush(fh);                                                                \
  } while (0)

cmd_status_t cmd_handle_listval(FILE *fh, char *buffer) {
  cmd_error_handler_t err = {cmd_error_fh, fh};
  cmd_status_t status;
  cmd_t cmd;

  char **names = NULL;
  cdtime_t *times = NULL;
  size_t number = 0;

  DEBUG("utils_cmd_listval: handle_listval (fh = %p, buffer = %s);", (void *)fh,
        buffer);

  if ((status = cmd_parse(buffer, &cmd, NULL, &err)) != CMD_OK)
    return (status);
  if (cmd.type != CMD_LISTVAL) {
    cmd_error(CMD_UNKNOWN_COMMAND, &err, "Unexpected command: `%s'.",
              CMD_TO_STRING(cmd.type));
    free_everything_and_return(CMD_UNKNOWN_COMMAND);
  }

  status = uc_get_names(&names, &times, &number);
  if (status != 0) {
    DEBUG("command listval: uc_get_names failed with status %i", status);
    cmd_error(CMD_ERROR, &err, "uc_get_names failed.");
    free_everything_and_return(CMD_ERROR);
  }

  print_to_socket(fh, "%i Value%s found\n", (int)number,
                  (number == 1) ? "" : "s");
  for (size_t i = 0; i < number; i++)
    print_to_socket(fh, "%.3f %s\n", CDTIME_T_TO_DOUBLE(times[i]), names[i]);

  free_everything_and_return(CMD_OK);
} /* cmd_status_t cmd_handle_listval */

void cmd_destroy_listval(cmd_listval_t *listval __attribute__((unused))) {
  /* nothing to do */
} /* void cmd_destroy_listval */

/* vim: set sw=2 sts=2 ts=8 : */

                             const cmd_options_t *opts,
                             cmd_error_handler_t *err) {

  if ((ret_flush == NULL) || (opts == NULL)) {
    errno = EINVAL;
    cmd_error(CMD_ERROR, err, "Invalid arguments to cmd_parse_flush.");
    return (CMD_ERROR);
  }

  for (size_t i = 0; i < argc; i++) {
    char *opt_key;
    char *opt_value;
    int status;

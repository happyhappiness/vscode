cmd_status_t cmd_parse_getval(size_t argc, char **argv,
                              cmd_getval_t *ret_getval,
                              const cmd_options_t *opts,
                              cmd_error_handler_t *err) {
  char *identifier_copy;
  int status;

  if ((ret_getval == NULL) || (opts == NULL)) {
    errno = EINVAL;
    cmd_error(CMD_ERROR, err, "Invalid arguments to cmd_parse_getval.");
    return CMD_ERROR;
  }

  if (argc != 1) {
    if (argc == 0)
      cmd_error(CMD_PARSE_ERROR, err, "Missing identifier.");
    else
      cmd_error(CMD_PARSE_ERROR, err, "Garbage after identifier: `%s'.",
                argv[1]);
    return CMD_PARSE_ERROR;
  }

  /* parse_identifier() modifies its first argument,
   * returning pointers into it */
  identifier_copy = sstrdup(argv[0]);

  status = parse_identifier(
      argv[0], &ret_getval->identifier.host, &ret_getval->identifier.plugin,
      &ret_getval->identifier.plugin_instance, &ret_getval->identifier.type,
      &ret_getval->identifier.type_instance, opts->identifier_default_host);
  if (status != 0) {
    DEBUG("cmd_parse_getval: Cannot parse identifier `%s'.", identifier_copy);
    cmd_error(CMD_PARSE_ERROR, err, "Cannot parse identifier `%s'.",
              identifier_copy);
    sfree(identifier_copy);
    return CMD_PARSE_ERROR;
  }

  ret_getval->raw_identifier = identifier_copy;
  return CMD_OK;
}
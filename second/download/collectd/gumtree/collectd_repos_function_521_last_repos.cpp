cmd_status_t cmd_parse_option(char *field, char **ret_key, char **ret_value,
                              cmd_error_handler_t *err) {
  char *key, *value;

  if (field == NULL) {
    errno = EINVAL;
    cmd_error(CMD_ERROR, err, "Invalid argument to cmd_parse_option.");
    return CMD_ERROR;
  }
  key = value = field;

  /* Look for the equal sign. */
  while (isalnum((int)value[0]) || (value[0] == '_') || (value[0] == ':'))
    value++;
  if ((value[0] != '=') || (value == key)) {
    /* Whether this is a fatal error is up to the caller. */
    return CMD_NO_OPTION;
  }
  *value = '\0';
  value++;

  if (ret_key != NULL)
    *ret_key = key;
  if (ret_value != NULL)
    *ret_value = value;

  return CMD_OK;
}
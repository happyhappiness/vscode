cmd_status_t cmd_parse(char *buffer, cmd_t *ret_cmd, const cmd_options_t *opts,
                       cmd_error_handler_t *err) {
  char **fields = NULL;
  size_t fields_num = 0;
  cmd_status_t status;

  if ((status = cmd_split(buffer, &fields_num, &fields, err)) != CMD_OK)
    return status;

  status = cmd_parsev(fields_num, fields, ret_cmd, opts, err);
  free(fields);
  return (status);
}
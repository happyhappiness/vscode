
  ret_putval->raw_identifier = identifier_copy;
  if (ret_putval->raw_identifier == NULL) {
    cmd_error(CMD_ERROR, err, "malloc failed.");
    cmd_destroy_putval(ret_putval);
    sfree(vl.values);
    return CMD_ERROR;
  }

  /* All the remaining fields are part of the option list. */
  result = CMD_OK;
  for (size_t i = 1; i < argc; ++i) {
    value_list_t *tmp;

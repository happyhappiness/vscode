void cmd_destroy_getval(cmd_getval_t *getval) {
  if (getval == NULL)
    return;

  sfree(getval->raw_identifier);
}
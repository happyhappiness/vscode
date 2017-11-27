int lcc_flush(lcc_connection_t *c, const char *plugin, /* {{{ */
              lcc_identifier_t *ident, int timeout) {
  char command[1024] = "";
  lcc_response_t res;
  int status;

  if (c == NULL) {
    lcc_set_errno(c, EINVAL);
    return (-1);
  }

  SSTRCPY(command, "FLUSH");

  if (timeout > 0)
    SSTRCATF(command, " timeout=%i", timeout);

  if (plugin != NULL) {
    char buffer[2 * LCC_NAME_LEN];
    SSTRCATF(command, " plugin=%s",
             lcc_strescape(buffer, plugin, sizeof(buffer)));
  }

  if (ident != NULL) {
    char ident_str[6 * LCC_NAME_LEN];
    char ident_esc[12 * LCC_NAME_LEN];

    status = lcc_identifier_to_string(c, ident_str, sizeof(ident_str), ident);
    if (status != 0)
      return (status);

    SSTRCATF(command, " identifier=%s",
             lcc_strescape(ident_esc, ident_str, sizeof(ident_esc)));
  }

  status = lcc_sendreceive(c, command, &res);
  if (status != 0)
    return (status);

  if (res.status != 0) {
    LCC_SET_ERRSTR(c, "Server error: %s", res.message);
    lcc_response_free(&res);
    return (-1);
  }

  lcc_response_free(&res);
  return (0);
}
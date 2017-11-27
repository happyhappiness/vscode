int lcc_listval(lcc_connection_t *c, /* {{{ */
                lcc_identifier_t **ret_ident, size_t *ret_ident_num) {
  lcc_response_t res;
  int status;

  lcc_identifier_t *ident;
  size_t ident_num;

  if (c == NULL)
    return -1;

  if ((ret_ident == NULL) || (ret_ident_num == NULL)) {
    lcc_set_errno(c, EINVAL);
    return -1;
  }

  status = lcc_sendreceive(c, "LISTVAL", &res);
  if (status != 0)
    return status;

  if (res.status != 0) {
    LCC_SET_ERRSTR(c, "Server error: %s", res.message);
    lcc_response_free(&res);
    return -1;
  }

  ident_num = res.lines_num;
  ident = malloc(ident_num * sizeof(*ident));
  if (ident == NULL) {
    lcc_response_free(&res);
    lcc_set_errno(c, ENOMEM);
    return -1;
  }

  for (size_t i = 0; i < res.lines_num; i++) {
    char *time_str;
    char *ident_str;

    /* First field is the time. */
    time_str = res.lines[i];

    /* Set `ident_str' to the beginning of the second field. */
    ident_str = time_str;
    while ((*ident_str != ' ') && (*ident_str != '\t') && (*ident_str != 0))
      ident_str++;
    while ((*ident_str == ' ') || (*ident_str == '\t')) {
      *ident_str = 0;
      ident_str++;
    }

    if (*ident_str == 0) {
      lcc_set_errno(c, EILSEQ);
      status = -1;
      break;
    }

    status = lcc_string_to_identifier(c, ident + i, ident_str);
    if (status != 0)
      break;
  }

  lcc_response_free(&res);

  if (status != 0) {
    free(ident);
    return -1;
  }

  *ret_ident = ident;
  *ret_ident_num = ident_num;

  return 0;
}
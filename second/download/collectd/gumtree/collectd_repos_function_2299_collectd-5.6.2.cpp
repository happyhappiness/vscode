int lcc_getval(lcc_connection_t *c, lcc_identifier_t *ident, /* {{{ */
               size_t *ret_values_num, gauge_t **ret_values,
               char ***ret_values_names) {
  char ident_str[6 * LCC_NAME_LEN];
  char ident_esc[12 * LCC_NAME_LEN];
  char command[14 * LCC_NAME_LEN];

  lcc_response_t res;
  size_t values_num;
  gauge_t *values = NULL;
  char **values_names = NULL;

  size_t i;
  int status;

  if (c == NULL)
    return (-1);

  if (ident == NULL) {
    lcc_set_errno(c, EINVAL);
    return (-1);
  }

  /* Build a commend with an escaped version of the identifier string. */
  status = lcc_identifier_to_string(c, ident_str, sizeof(ident_str), ident);
  if (status != 0)
    return (status);

  snprintf(command, sizeof(command), "GETVAL %s",
           lcc_strescape(ident_esc, ident_str, sizeof(ident_esc)));
  command[sizeof(command) - 1] = 0;

  /* Send talk to the daemon.. */
  status = lcc_sendreceive(c, command, &res);
  if (status != 0)
    return (status);

  if (res.status != 0) {
    LCC_SET_ERRSTR(c, "Server error: %s", res.message);
    lcc_response_free(&res);
    return (-1);
  }

  values_num = res.lines_num;

#define BAIL_OUT(e)                                                            \
  do {                                                                         \
    lcc_set_errno(c, (e));                                                     \
    free(values);                                                              \
    if (values_names != NULL) {                                                \
      for (i = 0; i < values_num; i++) {                                       \
        free(values_names[i]);                                                 \
      }                                                                        \
    }                                                                          \
    free(values_names);                                                        \
    lcc_response_free(&res);                                                   \
    return (-1);                                                               \
  } while (0)

  /* If neither the values nor the names are requested, return here.. */
  if ((ret_values == NULL) && (ret_values_names == NULL)) {
    if (ret_values_num != NULL)
      *ret_values_num = values_num;
    lcc_response_free(&res);
    return (0);
  }

  /* Allocate space for the values */
  if (ret_values != NULL) {
    values = malloc(values_num * sizeof(*values));
    if (values == NULL)
      BAIL_OUT(ENOMEM);
  }

  if (ret_values_names != NULL) {
    values_names = calloc(values_num, sizeof(*values_names));
    if (values_names == NULL)
      BAIL_OUT(ENOMEM);
  }

  for (i = 0; i < res.lines_num; i++) {
    char *key;
    char *value;
    char *endptr;

    key = res.lines[i];
    value = strchr(key, '=');
    if (value == NULL)
      BAIL_OUT(EILSEQ);

    *value = 0;
    value++;

    if (values != NULL) {
      endptr = NULL;
      errno = 0;
      values[i] = strtod(value, &endptr);

      if ((endptr == value) || (errno != 0))
        BAIL_OUT(errno);
    }

    if (values_names != NULL) {
      values_names[i] = strdup(key);
      if (values_names[i] == NULL)
        BAIL_OUT(ENOMEM);
    }
  } /* for (i = 0; i < res.lines_num; i++) */

  if (ret_values_num != NULL)
    *ret_values_num = values_num;
  if (ret_values != NULL)
    *ret_values = values;
  if (ret_values_names != NULL)
    *ret_values_names = values_names;

  lcc_response_free(&res);

  return (0);
}
static cmd_status_t cmd_split(char *buffer, size_t *ret_len, char ***ret_fields,
                              cmd_error_handler_t *err) {
  char *field;
  bool in_field, in_quotes;

  size_t estimate, len;
  char **fields;

  estimate = 0;
  in_field = false;
  for (char *string = buffer; *string != '\0'; ++string) {
    /* Make a quick worst-case estimate of the number of fields by
     * counting spaces and ignoring quotation marks. */
    if (!isspace((int)*string)) {
      if (!in_field) {
        estimate++;
        in_field = true;
      }
    } else {
      in_field = false;
    }
  }

  /* fields will be NULL-terminated */
  fields = malloc((estimate + 1) * sizeof(*fields));
  if (fields == NULL) {
    cmd_error(CMD_ERROR, err, "malloc failed.");
    return CMD_ERROR;
  }

#define END_FIELD()                                                            \
  do {                                                                         \
    *field = '\0';                                                             \
    field = NULL;                                                              \
    in_field = false;                                                          \
  } while (0)
#define NEW_FIELD()                                                            \
  do {                                                                         \
    field = string;                                                            \
    in_field = true;                                                           \
    assert(len < estimate);                                                    \
    fields[len] = field;                                                       \
    field++;                                                                   \
    len++;                                                                     \
  } while (0)

  len = 0;
  field = NULL;
  in_field = false;
  in_quotes = false;
  for (char *string = buffer; *string != '\0'; string++) {
    if (isspace((int)string[0])) {
      if (!in_quotes) {
        if (in_field)
          END_FIELD();

        /* skip space */
        continue;
      }
    } else if (string[0] == '"') {
      /* Note: Two consecutive quoted fields not separated by space are
       * treated as different fields. This is the collectd 5.x behavior
       * around splitting fields. */

      if (in_quotes) {
        /* end of quoted field */
        if (!in_field) /* empty quoted string */
          NEW_FIELD();
        END_FIELD();
        in_quotes = false;
        continue;
      }

      in_quotes = true;
      /* if (! in_field): add new field on next iteration
       * else: quoted string following an unquoted string (one field)
       * in either case: skip quotation mark */
      continue;
    } else if ((string[0] == '\\') && in_quotes) {
      /* Outside of quotes, a backslash is a regular character (mostly
       * for backward compatibility). */

      if (string[1] == '\0') {
        free(fields);
        cmd_error(CMD_PARSE_ERROR, err, "Backslash at end of string.");
        return CMD_PARSE_ERROR;
      }

      /* un-escape the next character; skip backslash */
      string++;
    }

    if (!in_field)
      NEW_FIELD();
    else {
      *field = string[0];
      field++;
    }
  }

  if (in_quotes) {
    free(fields);
    cmd_error(CMD_PARSE_ERROR, err, "Unterminated quoted string.");
    return CMD_PARSE_ERROR;
  }

#undef NEW_FIELD
#undef END_FIELD

  fields[len] = NULL;
  if (ret_len != NULL)
    *ret_len = len;
  if (ret_fields != NULL)
    *ret_fields = fields;
  else
    free(fields);
  return CMD_OK;
}
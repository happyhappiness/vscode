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
} /* int cmd_split */

/*
 * public API
 */


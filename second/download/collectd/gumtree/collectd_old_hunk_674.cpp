  }

  status = lcc_string_to_identifier(c, ident, ident_str);
  if (status != 0) {
    fprintf(stderr, "ERROR: Failed to parse identifier ``%s'': %s.\n",
            ident_str, lcc_strerror(c));
    return (-1);
  }
  return (0);
} /* parse_identifier */

static int getval(lcc_connection_t *c, int argc, char **argv) {
  lcc_identifier_t ident;

  size_t ret_values_num = 0;

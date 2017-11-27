static int parse_identifier(lcc_connection_t *c, const char *value,
                            lcc_identifier_t *ident) {
  char hostname[1024];
  char ident_str[1024] = "";
  int n_slashes;

  int status;

  n_slashes = count_chars(value, '/');
  if (n_slashes == 1) {
    /* The user has omitted the hostname part of the identifier
     * (there is only one '/' in the identifier)
     * Let's add the local hostname */
    if (gethostname(hostname, sizeof(hostname)) != 0) {
      fprintf(stderr, "ERROR: Failed to get local hostname: %s",
              strerror(errno));
      return -1;
    }
    hostname[sizeof(hostname) - 1] = '\0';

    snprintf(ident_str, sizeof(ident_str), "%s/%s", hostname, value);
    ident_str[sizeof(ident_str) - 1] = '\0';
  } else {
    strncpy(ident_str, value, sizeof(ident_str));
    ident_str[sizeof(ident_str) - 1] = '\0';
  }

  status = lcc_string_to_identifier(c, ident, ident_str);
  if (status != 0) {
    fprintf(stderr, "ERROR: Failed to parse identifier ``%s'': %s.\n",
            ident_str, lcc_strerror(c));
    return -1;
  }
  return 0;
}
  const char *str;

  struct addrinfo *ai_list;
  int status;

  str = global_option_get("Hostname");
  if (str != NULL) {
    sstrncpy(hostname_g, str, sizeof(hostname_g));
    return (0);
  }

  if (gethostname(hostname_g, sizeof(hostname_g)) != 0) {
    fprintf(stderr, "`gethostname' failed and no "

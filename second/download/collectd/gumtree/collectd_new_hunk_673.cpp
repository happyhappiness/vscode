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

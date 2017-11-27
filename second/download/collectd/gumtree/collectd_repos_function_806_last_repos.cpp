static int email_config(const char *key, const char *value) {
  if (strcasecmp(key, "SocketFile") == 0) {
    if (sock_file != NULL)
      free(sock_file);
    sock_file = sstrdup(value);
  } else if (strcasecmp(key, "SocketGroup") == 0) {
    if (sock_group != NULL)
      free(sock_group);
    sock_group = sstrdup(value);
  } else if (strcasecmp(key, "SocketPerms") == 0) {
    /* the user is responsible for providing reasonable values */
    sock_perms = (int)strtol(value, NULL, 8);
  } else if (strcasecmp(key, "MaxConns") == 0) {
    long int tmp = strtol(value, NULL, 0);

    if (tmp < 1) {
      fprintf(stderr, "email plugin: `MaxConns' was set to invalid "
                      "value %li, will use default %i.\n",
              tmp, MAX_CONNS);
      ERROR("email plugin: `MaxConns' was set to invalid "
            "value %li, will use default %i.\n",
            tmp, MAX_CONNS);
      max_conns = MAX_CONNS;
    } else if (tmp > MAX_CONNS_LIMIT) {
      fprintf(stderr, "email plugin: `MaxConns' was set to invalid "
                      "value %li, will use hardcoded limit %i.\n",
              tmp, MAX_CONNS_LIMIT);
      ERROR("email plugin: `MaxConns' was set to invalid "
            "value %li, will use hardcoded limit %i.\n",
            tmp, MAX_CONNS_LIMIT);
      max_conns = MAX_CONNS_LIMIT;
    } else {
      max_conns = (int)tmp;
    }
  } else {
    return -1;
  }
  return 0;
}
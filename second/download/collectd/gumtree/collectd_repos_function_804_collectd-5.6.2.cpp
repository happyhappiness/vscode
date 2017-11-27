static int email_config(const char *key, const char *value) {
  if (0 == strcasecmp(key, "SocketFile")) {
    if (NULL != sock_file)
      free(sock_file);
    sock_file = sstrdup(value);
  } else if (0 == strcasecmp(key, "SocketGroup")) {
    if (NULL != sock_group)
      free(sock_group);
    sock_group = sstrdup(value);
  } else if (0 == strcasecmp(key, "SocketPerms")) {
    /* the user is responsible for providing reasonable values */
    sock_perms = (int)strtol(value, NULL, 8);
  } else if (0 == strcasecmp(key, "MaxConns")) {
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
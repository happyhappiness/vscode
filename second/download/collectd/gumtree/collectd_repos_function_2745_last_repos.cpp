static int init_hostname(void) {
  const char *str = global_option_get("Hostname");
  if ((str != NULL) && (str[0] != 0)) {
    hostname_set(str);
    return 0;
  }

  long hostname_len = sysconf(_SC_HOST_NAME_MAX);
  if (hostname_len == -1) {
    hostname_len = NI_MAXHOST;
  }
  char hostname[hostname_len];

  if (gethostname(hostname, hostname_len) != 0) {
    fprintf(stderr, "`gethostname' failed and no "
                    "hostname was configured.\n");
    return -1;
  }

  hostname_set(hostname);

  str = global_option_get("FQDNLookup");
  if (IS_FALSE(str))
    return 0;

  struct addrinfo *ai_list;
  struct addrinfo ai_hints = {.ai_flags = AI_CANONNAME};

  int status = getaddrinfo(hostname, NULL, &ai_hints, &ai_list);
  if (status != 0) {
    ERROR("Looking up \"%s\" failed. You have set the "
          "\"FQDNLookup\" option, but I cannot resolve "
          "my hostname to a fully qualified domain "
          "name. Please fix the network "
          "configuration.",
          hostname);
    return -1;
  }

  for (struct addrinfo *ai_ptr = ai_list; ai_ptr != NULL;
       ai_ptr = ai_ptr->ai_next) {
    if (ai_ptr->ai_canonname == NULL)
      continue;

    hostname_set(ai_ptr->ai_canonname);
    break;
  }

  freeaddrinfo(ai_list);
  return 0;
}
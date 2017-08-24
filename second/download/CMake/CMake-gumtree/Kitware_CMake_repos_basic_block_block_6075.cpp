f(proxy && conn->unix_domain_socket) {
    free(proxy);
    proxy = NULL;
  }
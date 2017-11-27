int server_open(lcc_listener_t *srv) {
  struct addrinfo *res = NULL;
  int status = getaddrinfo(srv->node ? srv->node : "::",
                           srv->service ? srv->service : LCC_DEFAULT_PORT,
                           &(struct addrinfo){
                               .ai_flags = AI_ADDRCONFIG,
                               .ai_family = AF_UNSPEC,
                               .ai_socktype = SOCK_DGRAM,
                           },
                           &res);
  if (status != 0)
    return status;

  for (struct addrinfo *ai = res; ai != NULL; ai = ai->ai_next) {
    srv->conn = socket(ai->ai_family, ai->ai_socktype, 0);
    if (srv->conn == -1)
      continue;

    status = server_bind_socket(srv, ai);
    if (status != 0) {
      close(srv->conn);
      srv->conn = -1;
      continue;
    }

    break;
  }

  freeaddrinfo(res);

  if (srv->conn >= 0)
    return 0;
  return status != 0 ? status : -1;
}
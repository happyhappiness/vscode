static int server_bind_socket(lcc_listener_t *srv, struct addrinfo const *ai) {
  /* allow multiple sockets to use the same PORT number */
  if (setsockopt(srv->conn, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) ==
      -1
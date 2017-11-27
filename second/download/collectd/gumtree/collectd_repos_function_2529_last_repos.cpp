int lcc_listen_and_write(lcc_listener_t srv) {
  _Bool close_socket = 0;

  if (srv.conn < 0) {
    int status = server_open(&srv);
    if (status != 0)
      return status;
    close_socket = 1;
  }

  if (srv.buffer_size == 0)
    srv.buffer_size = LCC_NETWORK_BUFFER_SIZE;

  if (srv.parser == NULL)
    srv.parser = lcc_network_parse;

  int ret = 0;
  while (42) {
    char buffer[srv.buffer_size];
    ssize_t len = recv(srv.conn, buffer, sizeof(buffer), /* flags = */ 0);
    if (len == -1) {
      ret = errno;
      break;
    } else if (len == 0) {
      break;
    }

    (void)srv.parser(buffer, (size_t)len, srv.parse_options);
  }

  if (close_socket) {
    close(srv.conn);
    srv.conn = -1;
  }

  return ret;
}
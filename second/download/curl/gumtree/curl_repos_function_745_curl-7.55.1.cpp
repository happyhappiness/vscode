static curl_socket_t open_sock(void *ctx, curlsocktype purpose,
                               struct curl_sockaddr *address) {
  if(cur_size == -1) {
    fail("not fuzzing");
  }
  if(server_fd != -1 || client_fd != -1) {
    fail("already connected");
  }
  int fds[2];
  if(socketpair(AF_UNIX, SOCK_STREAM, 0, fds)) {
    fail("socketpair");
  }
  server_fd = fds[0];
  client_fd = fds[1];
  if(write(server_fd, cur_data, cur_size) != cur_size) {
    fail("write");
  }
  if(shutdown(server_fd, SHUT_WR)) {
    fail("shutdown");
  }
  return client_fd;
}
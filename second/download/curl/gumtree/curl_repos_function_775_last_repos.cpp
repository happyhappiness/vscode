static curl_socket_t fuzz_open_socket(void *ptr,
                                      curlsocktype purpose,
                                      struct curl_sockaddr *address)
{
  FUZZ_DATA *fuzz = (FUZZ_DATA *)ptr;
  int fds[2];
  curl_socket_t server_fd;
  curl_socket_t client_fd;

  /* Handle unused parameters */
  (void)purpose;
  (void)address;

  if(socketpair(AF_UNIX, SOCK_STREAM, 0, fds)) {
    /* Failed to create a pair of sockets. */
    return CURL_SOCKET_BAD;
  }

  server_fd = fds[0];
  client_fd = fds[1];

  /* Try and write the response data to the server file descriptor so the
     client can read it. */
  if(write(server_fd,
           fuzz->rsp1_data,
           fuzz->rsp1_data_len) != (ssize_t)fuzz->rsp1_data_len) {
    /* Failed to write the data. */
    return CURL_SOCKET_BAD;
  }

  if(shutdown(server_fd, SHUT_WR)) {
    return CURL_SOCKET_BAD;
  }

  return client_fd;
}
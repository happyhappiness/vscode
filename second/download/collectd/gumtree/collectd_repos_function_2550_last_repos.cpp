static int server_send_buffer(lcc_server_t *srv) /* {{{ */
{
  char buffer[LCC_NETWORK_BUFFER_SIZE_DEFAULT] = {0};
  size_t buffer_size;
  int status;

  if (srv->fd < 0) {
    status = server_open_socket(srv);
    if (status != 0)
      return status;
  }

  buffer_size = sizeof(buffer);

  status = lcc_network_buffer_finalize(srv->buffer);
  if (status != 0) {
    lcc_network_buffer_initialize(srv->buffer);
    return status;
  }

  status = lcc_network_buffer_get(srv->buffer, buffer, &buffer_size);
  lcc_network_buffer_initialize(srv->buffer);

  if (status != 0)
    return status;

  if (buffer_size > sizeof(buffer))
    buffer_size = sizeof(buffer);

  while (42) {
    assert(srv->fd >= 0);
    assert(srv->sa != NULL);
    status = (int)sendto(srv->fd, buffer, buffer_size, /* flags = */ 0, srv->sa,
                         srv->sa_len);
    if ((status < 0) && ((errno == EINTR) || (errno == EAGAIN)))
      continue;

    break;
  }

  if (status < 0)
    return status;
  return 0;
}
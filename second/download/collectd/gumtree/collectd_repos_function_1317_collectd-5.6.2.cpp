static void pinba_socket_free(pinba_socket_t *socket) /* {{{ */
{
  if (!socket)
    return;

  for (nfds_t i = 0; i < socket->fd_num; i++) {
    if (socket->fd[i].fd < 0)
      continue;
    close(socket->fd[i].fd);
    socket->fd[i].fd = -1;
  }

  sfree(socket);
}
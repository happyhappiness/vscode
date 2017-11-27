static int pb_del_socket(pinba_socket_t *s, /* {{{ */
                         nfds_t index) {
  if (index >= s->fd_num)
    return (EINVAL);

  close(s->fd[index].fd);
  s->fd[index].fd = -1;

  /* When deleting the last element in the list, no memmove is necessary. */
  if (index < (s->fd_num - 1)) {
    memmove(&s->fd[index], &s->fd[index + 1],
            sizeof(s->fd[0]) * (s->fd_num - (index + 1)));
  }

  s->fd_num--;
  return (0);
}
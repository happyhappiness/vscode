static int receive_loop(void) /* {{{ */
{
  pinba_socket_t *s;

  s = pinba_socket_open(conf_node, conf_service);
  if (s == NULL) {
    ERROR("pinba plugin: Collector thread is exiting prematurely.");
    return (-1);
  }

  while (!collector_thread_do_shutdown) {
    int status;

    if (s->fd_num < 1)
      break;

    status = poll(s->fd, s->fd_num, /* timeout = */ 1000);
    if (status == 0) /* timeout */
    {
      continue;
    } else if (status < 0) {
      char errbuf[1024];

      if ((errno == EINTR) || (errno == EAGAIN))
        continue;

      ERROR("pinba plugin: poll(2) failed: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
      pinba_socket_free(s);
      return (-1);
    }

    for (nfds_t i = 0; i < s->fd_num; i++) {
      if (s->fd[i].revents & (POLLERR | POLLHUP | POLLNVAL)) {
        pb_del_socket(s, i);
        i--;
      } else if (s->fd[i].revents & (POLLIN | POLLPRI)) {
        pinba_udp_read_callback_fn(s->fd[i].fd);
      }
    } /* for (s->fd) */
  }   /* while (!collector_thread_do_shutdown) */

  pinba_socket_free(s);
  s = NULL;

  return (0);
}
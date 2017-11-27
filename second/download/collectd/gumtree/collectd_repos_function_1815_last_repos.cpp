static void *statsd_network_thread(void *args) /* {{{ */
{
  struct pollfd *fds = NULL;
  size_t fds_num = 0;
  int status;

  status = statsd_network_init(&fds, &fds_num);
  if (status != 0) {
    ERROR("statsd plugin: Unable to open listening sockets.");
    pthread_exit((void *)0);
  }

  while (!network_thread_shutdown) {
    status = poll(fds, (nfds_t)fds_num, /* timeout = */ -1);
    if (status < 0) {
      char errbuf[1024];

      if ((errno == EINTR) || (errno == EAGAIN))
        continue;

      ERROR("statsd plugin: poll(2) failed: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
      break;
    }

    for (size_t i = 0; i < fds_num; i++) {
      if ((fds[i].revents & (POLLIN | POLLPRI)) == 0)
        continue;

      statsd_network_read(fds[i].fd);
      fds[i].revents = 0;
    }
  } /* while (!network_thread_shutdown) */

  /* Clean up */
  for (size_t i = 0; i < fds_num; i++)
    close(fds[i].fd);
  sfree(fds);

  return (void *)0;
}
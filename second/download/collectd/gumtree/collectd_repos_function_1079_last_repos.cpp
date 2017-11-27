static int socket_receive(socket_adapter_t *self, FILE **pp_file) {
  int res = -1;
  pthread_rwlock_rdlock(&self->lock);
  struct pollfd poll_fd = {
      .fd = self->sock_fd, .events = POLLIN | POLLPRI,
  };

  if ((res = poll(&poll_fd, 1, MCELOG_POLL_TIMEOUT)) <= 0) {
    if (res != 0 && errno != EINTR) {
      char errbuf[MCELOG_BUFF_SIZE];
      ERROR("mcelog: poll failed: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
    }
    pthread_rwlock_unlock(&self->lock);
    return res;
  }

  if (poll_fd.revents & (POLLERR | POLLHUP | POLLNVAL)) {
    /* connection is broken */
    ERROR(MCELOG_PLUGIN ": Connection to socket is broken");
    if (poll_fd.revents & (POLLERR | POLLHUP)) {
      mcelog_dispatch_notification(
          &(notification_t){.severity = NOTIF_FAILURE,
                            .time = cdtime(),
                            .message = "Connection to mcelog socket is broken.",
                            .plugin = MCELOG_PLUGIN,
                            .type_instance = "mcelog_status"});
    }
    pthread_rwlock_unlock(&self->lock);
    return -1;
  }

  if (!(poll_fd.revents & (POLLIN | POLLPRI))) {
    INFO(MCELOG_PLUGIN ": No data to read");
    pthread_rwlock_unlock(&self->lock);
    return 0;
  }

  if ((*pp_file = fdopen(dup(self->sock_fd), "r")) == NULL)
    res = -1;

  pthread_rwlock_unlock(&self->lock);
  return res;
}
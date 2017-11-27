static int socket_reinit(socket_adapter_t *self) {
  char errbuff[MCELOG_BUFF_SIZE];
  int ret = -1;
  cdtime_t interval = plugin_get_interval();
  struct timeval socket_timeout = CDTIME_T_TO_TIMEVAL(interval);

  /* synchronization via write lock since sock_fd may be changed here */
  pthread_rwlock_wrlock(&self->lock);
  self->sock_fd =
      socket(PF_UNIX, SOCK_STREAM | SOCK_CLOEXEC | SOCK_NONBLOCK, 0);
  if (self->sock_fd < 0) {
    ERROR(MCELOG_PLUGIN ": Could not create a socket. %s",
          sstrerror(errno, errbuff, sizeof(errbuff)));
    pthread_rwlock_unlock(&self->lock);
    return ret;
  }

  /* Set socket timeout option */
  if (setsockopt(self->sock_fd, SOL_SOCKET, SO_SNDTIMEO, &socket_timeout,
                 sizeof(socket_timeout)) < 0)
    ERROR(MCELOG_PLUGIN ": Failed to set the socket timeout option.");

  /* downgrading to read lock due to possible recursive read locks
   * in self->close(self) call */
  pthread_rwlock_unlock(&self->lock);
  pthread_rwlock_rdlock(&self->lock);
  if (connect(self->sock_fd, (struct sockaddr *)&(self->unix_sock),
              sizeof(self->unix_sock)) < 0) {
    ERROR(MCELOG_PLUGIN ": Failed to connect to mcelog server. %s",
          sstrerror(errno, errbuff, sizeof(errbuff)));
    self->close(self);
    ret = -1;
  } else {
    ret = 0;
    mcelog_dispatch_notification(
        &(notification_t){.severity = NOTIF_OKAY,
                          .time = cdtime(),
                          .message = "Connected to mcelog server",
                          .plugin = MCELOG_PLUGIN,
                          .type_instance = "mcelog_status"});
  }
  pthread_rwlock_unlock(&self->lock);
  return ret;
}
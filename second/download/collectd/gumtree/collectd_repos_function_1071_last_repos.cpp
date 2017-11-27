static int socket_close(socket_adapter_t *self) {
  int ret = 0;
  pthread_rwlock_rdlock(&self->lock);
  if (fcntl(self->sock_fd, F_GETFL) != -1) {
    char errbuf[MCELOG_BUFF_SIZE];
    if (shutdown(self->sock_fd, SHUT_RDWR) != 0) {
      ERROR(MCELOG_PLUGIN ": Socket shutdown failed: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
      ret = -1;
    }
    if (close(self->sock_fd) != 0) {
      ERROR(MCELOG_PLUGIN ": Socket close failed: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
      ret = -1;
    }
  }
  pthread_rwlock_unlock(&self->lock);
  return ret;
}
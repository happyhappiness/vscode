static int socket_write(socket_adapter_t *self, const char *msg,
                        const size_t len) {
  int ret = 0;
  pthread_rwlock_rdlock(&self->lock);
  if (swrite(self->sock_fd, msg, len) != 0)
    ret = -1;
  pthread_rwlock_unlock(&self->lock);
  return ret;
}
static void memcached_free(void *arg) {
  memcached_t *st = arg;
  if (st == NULL)
    return;

  if (st->fd >= 0) {
    shutdown(st->fd, SHUT_RDWR);
    close(st->fd);
    st->fd = -1;
  }

  sfree(st->name);
  sfree(st->host);
  sfree(st->socket);
  sfree(st->connhost);
  sfree(st->connport);
  sfree(st);
}
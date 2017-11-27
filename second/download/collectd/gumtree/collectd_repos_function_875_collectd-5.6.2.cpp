static void memcached_free(void *arg) {
  memcached_t *st = arg;
  if (st == NULL)
    return;

  sfree(st->name);
  sfree(st->socket);
  sfree(st->host);
  sfree(st->port);
  sfree(st);
}
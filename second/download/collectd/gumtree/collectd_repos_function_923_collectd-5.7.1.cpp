static void memcached_free(void *arg) {
  memcached_t *st = arg;
  if (st == NULL)
    return;

  sfree(st->name);
  sfree(st->host);
  sfree(st->socket);
  sfree(st->connhost);
  sfree(st->connport);
  sfree(st);
}
static void memcached_connect(memcached_t *st) {
  if (st->fd >= 0)
    return;

  if (st->socket != NULL)
    st->fd = memcached_connect_unix(st);
  else
    st->fd = memcached_connect_inet(st);

  if (st->fd >= 0)
    INFO("memcached plugin: Instance \"%s\": connection established.",
         st->name);
}
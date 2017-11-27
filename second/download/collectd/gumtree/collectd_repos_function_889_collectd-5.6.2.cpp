static int memcached_init(void) {
  memcached_t *st;
  int status;

  if (memcached_have_instances)
    return (0);

  /* No instances were configured, lets start a default instance. */
  st = calloc(1, sizeof(*st));
  if (st == NULL)
    return (ENOMEM);
  st->name = sstrdup("__legacy__");
  st->socket = NULL;
  st->host = NULL;
  st->port = NULL;

  status = memcached_add_read_callback(st);
  if (status == 0)
    memcached_have_instances = 1;
  else
    memcached_free(st);

  return (status);
}
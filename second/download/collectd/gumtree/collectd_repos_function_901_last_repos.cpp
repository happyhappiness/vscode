static int memcached_init(void) {

  if (memcached_have_instances)
    return 0;

  /* No instances were configured, lets start a default instance. */
  memcached_t *st = calloc(1, sizeof(*st));
  if (st == NULL)
    return ENOMEM;
  st->name = NULL;
  st->host = NULL;
  st->socket = NULL;
  st->connhost = NULL;
  st->connport = NULL;

  st->fd = -1;

  int status = memcached_add_read_callback(st);
  if (status == 0)
    memcached_have_instances = 1;

  return status;
}
static int memcached_add_read_callback(memcached_t *st) {
  char callback_name[3 * DATA_MAX_NAME_LEN];
  int status;

  ssnprintf(callback_name, sizeof(callback_name), "memcached/%s",
            (st->name != NULL) ? st->name : "__legacy__");

  /* If no <Address> used then:
   * - Connect to the destination specified by <Host>, if present.
   *   If not, use the default address.
   * - Use the default hostname (set st->host to NULL), if
   *    - Legacy mode is used (no configuration options at all), or
   *    - "Host" option is not provided, or
   *    - "Host" option is set to "localhost" or "127.0.0.1".
   *
   * If <Address> used then host may be set to "localhost" or "127.0.0.1"
   * explicitly.
   */
  if (st->connhost == NULL) {
    if (st->host) {
      st->connhost = strdup(st->host);
      if (st->connhost == NULL)
        return (ENOMEM);

      if ((strcmp("127.0.0.1", st->host) == 0) ||
          (strcmp("localhost", st->host) == 0))
        sfree(st->host);
    } else {
      st->connhost = strdup(MEMCACHED_DEF_HOST);
      if (st->connhost == NULL)
        return (ENOMEM);
    }
  }

  if (st->connport == NULL) {
    st->connport = strdup(MEMCACHED_DEF_PORT);
    if (st->connport == NULL)
      return (ENOMEM);
  }

  assert(st->connhost != NULL);
  assert(st->connport != NULL);

  status = plugin_register_complex_read(
      /* group = */ "memcached",
      /* name      = */ callback_name,
      /* callback  = */ memcached_read,
      /* interval  = */ 0, &(user_data_t){
                               .data = st, .free_func = memcached_free,
                           });

  return (status);
}
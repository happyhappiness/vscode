static void memcached_init_vl(value_list_t *vl, memcached_t const *st) {
  char const *host = st->host;

  /* Set vl->host to hostname_g, if:
   * - Legacy mode is used.
   * - "Socket" option is given (doc: "Host option is ignored").
   * - "Host" option is not provided.
   * - "Host" option is set to "localhost" or "127.0.0.1". */
  if ((strcmp(st->name, "__legacy__") == 0) || (st->socket != NULL) ||
      (st->host == NULL) || (strcmp("127.0.0.1", st->host) == 0) ||
      (strcmp("localhost", st->host) == 0))
    host = hostname_g;

  sstrncpy(vl->plugin, "memcached", sizeof(vl->plugin));
  sstrncpy(vl->host, host, sizeof(vl->host));
  if (strcmp(st->name, "__legacy__") != 0)
    sstrncpy(vl->plugin_instance, st->name, sizeof(vl->plugin_instance));
}
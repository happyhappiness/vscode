static void memcached_init_vl(value_list_t *vl, memcached_t const *st) {
  sstrncpy(vl->plugin, "memcached", sizeof(vl->plugin));
  if (st->host != NULL)
    sstrncpy(vl->host, st->host, sizeof(vl->host));
  if (st->name != NULL)
    sstrncpy(vl->plugin_instance, st->name, sizeof(vl->plugin_instance));
}
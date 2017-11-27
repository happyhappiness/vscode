static int memcached_add_read_callback(memcached_t *st) {
  char callback_name[3 * DATA_MAX_NAME_LEN];

  if (memcached_set_defaults(st) != 0) {
    memcached_free(st);
    return -1;
  }

  snprintf(callback_name, sizeof(callback_name), "memcached/%s",
           (st->name != NULL) ? st->name : "__legacy__");

  return plugin_register_complex_read(
      /* group = */ "memcached",
      /* name      = */ callback_name,
      /* callback  = */ memcached_read,
      /* interval  = */ 0,
      &(user_data_t){
          .data = st, .free_func = memcached_free,
      });
}
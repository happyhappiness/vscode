static int memcached_add_read_callback (memcached_t *st)
{
  char callback_name[3*DATA_MAX_NAME_LEN];
  int status;

  assert (st->name != NULL);
  ssnprintf (callback_name, sizeof (callback_name), "memcached/%s", st->name);

  user_data_t ud = {
    .data = st,
    .free_func = memcached_free
  };

  status = plugin_register_complex_read (/* group = */ "memcached",
      /* name      = */ callback_name,
      /* callback  = */ memcached_read,
      /* interval  = */ 0,
      /* user_data = */ &ud);
  return (status);
}
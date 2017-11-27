static int memcached_add_read_callback (memcached_t *st)
{
  user_data_t ud;
  char callback_name[3*DATA_MAX_NAME_LEN];
  int status;

  memset (&ud, 0, sizeof (ud));
  ud.data = st;
  ud.free_func = (void *) memcached_free;

  assert (st->name != NULL);
  ssnprintf (callback_name, sizeof (callback_name), "memcached/%s", st->name);

  status = plugin_register_complex_read (/* group = */ "memcached",
      /* name      = */ callback_name,
      /* callback  = */ memcached_read,
      /* interval  = */ NULL,
      /* user_data = */ &ud);
  return (status);
}
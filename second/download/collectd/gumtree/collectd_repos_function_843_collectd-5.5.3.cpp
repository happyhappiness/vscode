static int memcached_connect (memcached_t *st)
{
  if (st->socket != NULL)
    return (memcached_connect_unix (st));
  else
    return (memcached_connect_inet (st));
}
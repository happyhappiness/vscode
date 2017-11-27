static void memcached_free (memcached_t *st)
{
  if (st == NULL)
    return;

  sfree (st->name);
  sfree (st->socket);
  sfree (st->host);
  sfree (st->port);
  sfree (st);
}
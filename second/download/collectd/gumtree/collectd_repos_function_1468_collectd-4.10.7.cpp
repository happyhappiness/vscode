static int cmc_page_init_memc (web_page_t *wp) /* {{{ */
{
  memcached_server_st *server;

  wp->memc = memcached_create(NULL);
  if (wp->memc == NULL)
  {
    ERROR ("memcachec plugin: memcached_create failed.");
    return (-1);
  }

  server = memcached_servers_parse (wp->server);
  memcached_server_push (wp->memc, server);
  memcached_server_list_free (server);

  return (0);
}
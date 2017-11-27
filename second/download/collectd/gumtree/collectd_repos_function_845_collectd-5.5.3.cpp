static void memcached_init_vl (value_list_t *vl, memcached_t const *st)
{
  sstrncpy (vl->plugin, "memcached", sizeof (vl->plugin));
  if (strcmp (st->name, "__legacy__") == 0) /* legacy mode */
  {
    sstrncpy (vl->host, hostname_g, sizeof (vl->host));
  }
  else
  {
    if (st->socket != NULL)
      sstrncpy (vl->host, hostname_g, sizeof (vl->host));
    else
      sstrncpy (vl->host,
          (st->host != NULL) ? st->host : MEMCACHED_DEF_HOST,
          sizeof (vl->host));
    sstrncpy (vl->plugin_instance, st->name, sizeof (vl->plugin_instance));
  }
}
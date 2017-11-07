static void mutt_group_remove (group_t *g)
{
  if (!g)
    return;
  hash_delete (Groups, g->name, g, NULL);
  rfc822_free_address (&g->as);
  mutt_free_rx_list (&g->rs);
  FREE(&g->name);
  FREE(&g);
}
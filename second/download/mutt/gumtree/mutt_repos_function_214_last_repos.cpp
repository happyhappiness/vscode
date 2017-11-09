static int mutt_group_remove_rx (group_t *g, const char *s)
{
  return mutt_remove_from_rx_list (&g->rs, s);
}
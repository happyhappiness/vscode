static int mutt_group_add_rx (group_t *g, const char *s, int flags, BUFFER *err)
{
  return mutt_add_to_rx_list (&g->rs, s, flags, err);
}
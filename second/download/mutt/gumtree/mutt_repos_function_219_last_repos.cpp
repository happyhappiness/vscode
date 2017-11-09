int mutt_group_match (group_t *g, const char *s)
{
  ADDRESS *ap;

  if (s && g)
  {
    if (mutt_match_rx_list (s, g->rs))
      return 1;
    for (ap = g->as; ap; ap = ap->next)
      if (ap->mailbox && !mutt_strcasecmp (s, ap->mailbox))
	return 1;
  }
  return 0;
}
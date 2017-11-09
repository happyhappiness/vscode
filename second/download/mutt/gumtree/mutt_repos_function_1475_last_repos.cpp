int mutt_match_rx_list (const char *s, RX_LIST *l)
{
  if (!s)  return 0;
  
  for (; l; l = l->next)
  {
    if (regexec (l->rx->rx, s, (size_t) 0, (regmatch_t *) 0, (int) 0) == 0)
    {
      dprint (5, (debugfile, "mutt_match_rx_list: %s matches %s\n", s, l->rx->pattern));
      return 1;
    }
  }

  return 0;
}
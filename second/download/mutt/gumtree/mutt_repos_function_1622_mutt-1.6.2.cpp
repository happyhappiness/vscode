int mutt_add_to_rx_list (RX_LIST **list, const char *s, int flags, BUFFER *err)
{
  RX_LIST *t, *last = NULL;
  REGEXP *rx;

  if (!s || !*s)
    return 0;

  if (!(rx = mutt_compile_regexp (s, flags)))
  {
    snprintf (err->data, err->dsize, "Bad regexp: %s\n", s);
    return -1;
  }

  /* check to make sure the item is not already on this list */
  for (last = *list; last; last = last->next)
  {
    if (ascii_strcasecmp (rx->pattern, last->rx->pattern) == 0)
    {
      /* already on the list, so just ignore it */
      last = NULL;
      break;
    }
    if (!last->next)
      break;
  }

  if (!*list || last)
  {
    t = mutt_new_rx_list();
    t->rx = rx;
    if (last)
    {
      last->next = t;
      last = last->next;
    }
    else
      *list = last = t;
  }
  else /* duplicate */
    mutt_free_regexp (&rx);

  return 0;
}
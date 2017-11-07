int mutt_history_at_scratch (history_class_t hclass)
{
  struct history *h = GET_HISTORY(hclass);

  if (!HistSize || !h)
    return 0; /* disabled */

  return h->cur == h->last;
}
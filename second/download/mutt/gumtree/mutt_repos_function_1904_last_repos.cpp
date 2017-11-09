void mutt_reset_history_state (history_class_t hclass)
{
  struct history *h = GET_HISTORY(hclass);

  if (!HistSize || !h)
    return; /* disabled */

  h->cur = h->last;
}
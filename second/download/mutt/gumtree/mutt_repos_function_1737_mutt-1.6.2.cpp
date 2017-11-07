char *mutt_history_next (history_class_t hclass)
{
  int next;
  struct history *h = GET_HISTORY(hclass);

  if (!HistSize || !h)
    return (""); /* disabled */

  next = h->cur + 1;
  if (next > HistSize)
    next = 0;
  if (h->hist[next] || (next == h->last))
    h->cur = next;
  else
    h->cur = 0;
  return (h->hist[h->cur] ? h->hist[h->cur] : "");
}
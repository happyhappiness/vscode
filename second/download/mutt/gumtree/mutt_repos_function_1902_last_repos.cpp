char *mutt_history_next (history_class_t hclass)
{
  int next;
  struct history *h = GET_HISTORY(hclass);

  if (!HistSize || !h)
    return (""); /* disabled */

  next = h->cur;
  do
  {
    next++;
    if (next > HistSize)
      next = 0;
    if (next == h->last)
      break;
  } while (h->hist[next] == NULL);

  h->cur = next;
  return (h->hist[h->cur] ? h->hist[h->cur] : "");
}
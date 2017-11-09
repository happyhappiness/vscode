char *mutt_history_prev (history_class_t hclass)
{
  int prev;
  struct history *h = GET_HISTORY(hclass);

  if (!HistSize || !h)
    return (""); /* disabled */

  prev = h->cur;
  do
  {
    prev--;
    if (prev < 0)
      prev = HistSize;
    if (prev == h->last)
      break;
  } while (h->hist[prev] == NULL);

  h->cur = prev;
  return (h->hist[h->cur] ? h->hist[h->cur] : "");
}
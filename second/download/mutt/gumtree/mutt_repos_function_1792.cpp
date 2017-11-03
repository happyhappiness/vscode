char *mutt_history_prev (history_class_t hclass)
{
  int prev;
  struct history *h = GET_HISTORY(hclass);

  if (!HistSize || !h)
    return (""); /* disabled */

  prev = h->cur - 1;
  if (prev < 0)
  {
    prev = HistSize;
    while ((prev > 0) && (prev != h->last) && (h->hist[prev] == NULL))
      prev--;
  }
  if (h->hist[prev] || (prev == h->last))
    h->cur = prev;
  return (h->hist[h->cur] ? h->hist[h->cur] : "");
}
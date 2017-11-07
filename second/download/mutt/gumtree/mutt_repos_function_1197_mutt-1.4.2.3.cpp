char *mutt_history_prev (history_class_t hclass)
{
  int prev;
  struct history *h = &History[hclass];

  if (!HistSize)
    return (""); /* disabled */

  prev = h->cur - 1;
  if (prev < 0)
  {
    prev = HistSize - 1;
    while (prev > 0 && h->hist[prev] == NULL)
      prev--;
  }
  if (h->hist[prev])
    h->cur = prev;
  return (h->hist[h->cur] ? h->hist[h->cur] : "");
}
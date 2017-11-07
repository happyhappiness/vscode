char *mutt_history_next (history_class_t hclass)
{
  int next;
  struct history *h = &History[hclass];
  
  if (!HistSize)
    return (""); /* disabled */

  next = h->cur + 1;
  if (next > HistSize - 1)
    next = 0;
  h->cur = h->hist[next] ? next : 0;
  return (h->hist[h->cur] ? h->hist[h->cur] : "");
}
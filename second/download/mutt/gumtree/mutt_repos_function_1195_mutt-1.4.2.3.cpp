void mutt_history_add (history_class_t hclass, const char *s)
{
  int prev;
  struct history *h = &History[hclass];
  
  if (!HistSize)
    return; /* disabled */

  if (*s)
  {
    prev = h->last - 1;
    if (prev < 0) prev = HistSize - 1;
    if (!h->hist[prev] || mutt_strcmp (h->hist[prev], s) != 0)
    {
      mutt_str_replace (&h->hist[h->last++], s);
      if (h->last > HistSize - 1)
	h->last = 0;
    }
  }
  h->cur = h->last; /* reset to the last entry */
}
static void remove_history_dups (history_class_t hclass, const char *s)
{
  int source, dest, old_last;
  struct history *h = GET_HISTORY(hclass);

  if (!HistSize || !h)
    return; /* disabled */

  /* Remove dups from 0..last-1 compacting up. */
  source = dest = 0;
  while (source < h->last)
  {
    if (!mutt_strcmp (h->hist[source], s))
      FREE (&h->hist[source++]);
    else
      h->hist[dest++] = h->hist[source++];
  }

  /* Move 'last' entry up. */
  h->hist[dest] = h->hist[source];
  old_last = h->last;
  h->last = dest;

  /* Fill in moved entries with NULL */
  while (source > h->last)
    h->hist[source--] = NULL;

  /* Remove dups from last+1 .. HistSize compacting down. */
  source = dest = HistSize;
  while (source > old_last)
  {
    if (!mutt_strcmp (h->hist[source], s))
      FREE (&h->hist[source--]);
    else
      h->hist[dest--] = h->hist[source--];
  }

  /* Fill in moved entries with NULL */
  while (dest > old_last)
    h->hist[dest--] = NULL;
}
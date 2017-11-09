void mutt_history_add (history_class_t hclass, const char *s, int save)
{
  int prev;
  struct history *h = GET_HISTORY(hclass);

  if (!HistSize || !h)
    return; /* disabled */

  if (*s)
  {
    prev = h->last - 1;
    if (prev < 0) prev = HistSize;

    /* don't add to prompt history:
     *  - lines beginning by a space
     *  - repeated lines
     */
    if (*s != ' ' && (!h->hist[prev] || mutt_strcmp (h->hist[prev], s) != 0))
    {
      if (option (OPTHISTREMOVEDUPS))
        remove_history_dups (hclass, s);
      if (save && SaveHist)
        save_history (hclass, s);
      mutt_str_replace (&h->hist[h->last++], s);
      if (h->last > HistSize)
	h->last = 0;
    }
  }
  h->cur = h->last; /* reset to the last entry */
}
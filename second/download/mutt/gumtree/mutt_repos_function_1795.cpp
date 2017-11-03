void mutt_history_save_scratch (history_class_t hclass, const char *s)
{
  struct history *h = GET_HISTORY(hclass);

  if (!HistSize || !h)
    return; /* disabled */

  /* Don't check if s has a value because the scratch buffer may contain
   * an old garbage value that should be overwritten */
  mutt_str_replace (&h->hist[h->last], s);
}
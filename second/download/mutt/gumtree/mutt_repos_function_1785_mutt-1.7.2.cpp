static void init_history (struct history *h)
{
  int i;

  if(OldSize)
  {
    if (h->hist)
    {
      for (i = 0 ; i <= OldSize ; i ++)
	FREE (&h->hist[i]);
      FREE (&h->hist);
    }
  }
  
  if (HistSize)
    h->hist = safe_calloc (HistSize + 1, sizeof (char *));
  
  h->cur = 0;
  h->last = 0;
}
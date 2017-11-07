static void init_history (struct history *h)
{
  int i;

  if(OldSize)
  {
    if (h->hist)
    {
      for (i = 0 ; i < OldSize ; i ++)
	safe_free ((void **) &h->hist[i]);
      safe_free ((void **) &h->hist);
    }
  }
  
  if (HistSize)
    h->hist = safe_calloc (HistSize, sizeof (char *));
  
  h->cur = 0;
  h->last = 0;
}
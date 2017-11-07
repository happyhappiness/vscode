void mutt_menuDestroy (MUTTMENU **p)
{
  int i;

  safe_free ((void **) &(*p)->searchBuf);

  if ((*p)->dialog) 
  {
    for (i=0; i < (*p)->max; i++)
      safe_free ((void **) &(*p)->dialog[i]);

    safe_free ((void **) (*p)->dialog);
  }

  safe_free ((void **) p);
}
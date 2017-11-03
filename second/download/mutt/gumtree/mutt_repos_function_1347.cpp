void mutt_menuDestroy (MUTTMENU **p)
{
  int i;

  if ((*p)->dialog)
  {
    for (i=0; i < (*p)->max; i++)
      FREE (&(*p)->dialog[i]);

    FREE (& (*p)->dialog);
  }

  FREE (p);		/* __FREE_CHECKED__ */
}
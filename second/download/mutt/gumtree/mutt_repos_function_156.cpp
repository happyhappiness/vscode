void safe_realloc (void *ptr, size_t siz)
{
  void *r;
  void **p = (void **)ptr;

  if (siz == 0)
  {
    if (*p)
    {
      free (*p);			/* __MEM_CHECKED__ */
      *p = NULL;
    }
    return;
  }

  if (*p)
    r = (void *) realloc (*p, siz);	/* __MEM_CHECKED__ */
  else
  {
    /* realloc(NULL, nbytes) doesn't seem to work under SunOS 4.1.x  --- __MEM_CHECKED__ */
    r = (void *) malloc (siz);		/* __MEM_CHECKED__ */
  }

  if (!r)
  {
    mutt_error _("Out of memory!");
    sleep (1);
    mutt_exit (1);
  }

  *p = r;
}
void safe_free (void *ptr)	/* __SAFE_FREE_CHECKED__ */
{
  void **p = (void **)ptr;
  if (*p)
  {
    free (*p);				/* __MEM_CHECKED__ */
    *p = 0;
  }
}
void safe_free (void **p)
{
  if (*p)
  {
    free (*p);				/* __MEM_CHECKED__ */
    *p = 0;
  }
}
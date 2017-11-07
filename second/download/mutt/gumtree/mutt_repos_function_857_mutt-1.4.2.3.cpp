int safe_free (void **p)
{
  free(*p);		/* __MEM_CHECKED__ */
  *p = 0;
}
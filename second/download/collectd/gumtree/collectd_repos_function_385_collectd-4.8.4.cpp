int uc_init (void)
{
  if (cache_tree == NULL)
    cache_tree = c_avl_create ((int (*) (const void *, const void *))
	cache_compare);

  return (0);
}
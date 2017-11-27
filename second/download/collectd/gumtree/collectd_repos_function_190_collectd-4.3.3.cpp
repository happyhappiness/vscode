static value_cache_t *cache_search (const char *name)
{
	value_cache_t *vc;

	for (vc = cache_head; vc != NULL; vc = vc->next)
	{
		if (strcmp (vc->name, name) == 0)
			break;
	} /* for vc = cache_head .. NULL */

	return (vc);
}
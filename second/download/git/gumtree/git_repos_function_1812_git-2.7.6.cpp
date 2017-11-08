void clear_delta_base_cache(void)
{
	unsigned long p;
	for (p = 0; p < MAX_DELTA_CACHE; p++)
		release_delta_base_cache(&delta_base_cache[p]);
}
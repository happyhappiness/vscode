void submodule_free(void)
{
	cache_free(&cache);
	is_cache_init = 0;
}
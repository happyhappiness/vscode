void submodule_free(void)
{
	cache_free(&the_submodule_cache);
	is_cache_init = 0;
}
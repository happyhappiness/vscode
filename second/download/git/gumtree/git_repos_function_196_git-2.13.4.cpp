const struct submodule *submodule_from_name(const unsigned char *treeish_name,
		const char *name)
{
	ensure_cache_init();
	return config_from(&the_submodule_cache, treeish_name, name, lookup_name);
}
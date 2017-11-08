const struct submodule *submodule_from_path(const unsigned char *treeish_name,
		const char *path)
{
	ensure_cache_init();
	return config_from(&the_submodule_cache, treeish_name, path, lookup_path);
}
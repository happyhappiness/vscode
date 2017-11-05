const struct submodule *submodule_from_name(const unsigned char *commit_sha1,
		const char *name)
{
	ensure_cache_init();
	return config_from_name(&cache, commit_sha1, name);
}
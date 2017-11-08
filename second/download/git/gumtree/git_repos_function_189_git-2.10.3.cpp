const struct submodule *submodule_from_path(const unsigned char *commit_sha1,
		const char *path)
{
	ensure_cache_init();
	return config_from_path(&the_submodule_cache, commit_sha1, path);
}
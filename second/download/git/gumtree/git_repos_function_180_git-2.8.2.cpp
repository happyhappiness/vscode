static const struct submodule *config_from_path(struct submodule_cache *cache,
		const unsigned char *commit_sha1, const char *path)
{
	return config_from(cache, commit_sha1, path, lookup_path);
}
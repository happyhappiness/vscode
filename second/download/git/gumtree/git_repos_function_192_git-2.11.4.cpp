static const struct submodule *config_from_name(struct submodule_cache *cache,
		const unsigned char *commit_sha1, const char *name)
{
	return config_from(cache, commit_sha1, name, lookup_name);
}
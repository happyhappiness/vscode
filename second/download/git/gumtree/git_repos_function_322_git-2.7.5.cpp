struct cache_entry *make_cache_entry(unsigned int mode,
		const unsigned char *sha1, const char *path, int stage,
		unsigned int refresh_options)
{
	int size, len;
	struct cache_entry *ce, *ret;

	if (!verify_path(path)) {
		error("Invalid path '%s'", path);
		return NULL;
	}

	len = strlen(path);
	size = cache_entry_size(len);
	ce = xcalloc(1, size);

	hashcpy(ce->sha1, sha1);
	memcpy(ce->name, path, len);
	ce->ce_flags = create_ce_flags(stage);
	ce->ce_namelen = len;
	ce->ce_mode = create_ce_mode(mode);

	ret = refresh_cache_entry(ce, refresh_options);
	if (ret != ce)
		free(ce);
	return ret;
}
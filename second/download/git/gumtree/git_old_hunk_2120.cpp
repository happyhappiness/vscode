
struct cache_entry *make_cache_entry(unsigned int mode,
		const unsigned char *sha1, const char *path, int stage,
		unsigned int refresh_options)
{
	int size, len;
	struct cache_entry *ce;

	if (!verify_path(path)) {
		error("Invalid path '%s'", path);
		return NULL;
	}


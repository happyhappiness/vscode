	if (S_ISDIR(st.st_mode))
		return process_directory(path, len, &st);

	return add_one_path(ce, path, len, &st);
}

static int add_cacheinfo(unsigned int mode, const unsigned char *sha1,
			 const char *path, int stage)
{
	int size, len, option;
	struct cache_entry *ce;

	if (!verify_path(path))
		return error("Invalid path '%s'", path);

	len = strlen(path);
	size = cache_entry_size(len);
	ce = xcalloc(1, size);

	hashcpy(ce->sha1, sha1);
	memcpy(ce->name, path, len);
	ce->ce_flags = create_ce_flags(stage);
	ce->ce_namelen = len;
	ce->ce_mode = create_ce_mode(mode);
	if (assume_unchanged)
		ce->ce_flags |= CE_VALID;

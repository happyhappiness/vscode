static int update_some(const unsigned char *sha1, const char *base, int baselen,
		const char *pathname, unsigned mode, int stage, void *context)
{
	int len;
	struct cache_entry *ce;

	if (S_ISDIR(mode))
		return READ_TREE_RECURSIVE;

	len = baselen + strlen(pathname);
	ce = xcalloc(1, cache_entry_size(len));
	hashcpy(ce->sha1, sha1);
	memcpy(ce->name, base, baselen);
	memcpy(ce->name + baselen, pathname, len - baselen);
	ce->ce_flags = create_ce_flags(0) | CE_UPDATE;
	ce->ce_namelen = len;
	ce->ce_mode = create_ce_mode(mode);
	add_cache_entry(ce, ADD_CACHE_OK_TO_ADD | ADD_CACHE_OK_TO_REPLACE);
	return 0;
}
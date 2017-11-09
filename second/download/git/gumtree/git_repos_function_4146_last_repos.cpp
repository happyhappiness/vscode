static int read_one_entry_opt(struct index_state *istate,
			      const unsigned char *sha1,
			      const char *base, int baselen,
			      const char *pathname,
			      unsigned mode, int stage, int opt)
{
	int len;
	unsigned int size;
	struct cache_entry *ce;

	if (S_ISDIR(mode))
		return READ_TREE_RECURSIVE;

	len = strlen(pathname);
	size = cache_entry_size(baselen + len);
	ce = xcalloc(1, size);

	ce->ce_mode = create_ce_mode(mode);
	ce->ce_flags = create_ce_flags(stage);
	ce->ce_namelen = baselen + len;
	memcpy(ce->name, base, baselen);
	memcpy(ce->name + baselen, pathname, len+1);
	hashcpy(ce->oid.hash, sha1);
	return add_index_entry(istate, ce, opt);
}
static int add_one_path(const struct cache_entry *old, const char *path, int len, struct stat *st)
{
	int option, size;
	struct cache_entry *ce;

	/* Was the old index entry already up-to-date? */
	if (old && !ce_stage(old) && !ce_match_stat(old, st, 0))
		return 0;

	size = cache_entry_size(len);
	ce = xcalloc(1, size);
	memcpy(ce->name, path, len);
	ce->ce_flags = create_ce_flags(0);
	ce->ce_namelen = len;
	fill_stat_cache_info(ce, st);
	ce->ce_mode = ce_mode_from_stat(old, st->st_mode);

	if (index_path(ce->oid.hash, path, st,
		       info_only ? 0 : HASH_WRITE_OBJECT)) {
		free(ce);
		return -1;
	}
	option = allow_add ? ADD_CACHE_OK_TO_ADD : 0;
	option |= allow_replace ? ADD_CACHE_OK_TO_REPLACE : 0;
	if (add_cache_entry(ce, option))
		return error("%s: cannot add to the index - missing --add option?", path);
	return 0;
}
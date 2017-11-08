struct cache_entry *index_dir_exists(struct index_state *istate, const char *name, int namelen)
{
	struct cache_entry *ce;
	struct dir_entry *dir;

	lazy_init_name_hash(istate);
	dir = find_dir_entry(istate, name, namelen);
	if (dir && dir->nr)
		return dir->ce;

	/*
	 * It might be a submodule. Unlike plain directories, which are stored
	 * in the dir-hash, submodules are stored in the name-hash, so check
	 * there, as well.
	 */
	ce = index_file_exists(istate, name, namelen, 1);
	if (ce && S_ISGITLINK(ce->ce_mode))
		return ce;

	return NULL;
}
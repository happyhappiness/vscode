static struct dir_entry *hash_dir_entry(struct index_state *istate,
		struct cache_entry *ce, int namelen)
{
	/*
	 * Throw each directory component in the hash for quick lookup
	 * during a git status. Directory components are stored without their
	 * closing slash.  Despite submodules being a directory, they never
	 * reach this point, because they are stored
	 * in index_state.name_hash (as ordinary cache_entries).
	 *
	 * Note that the cache_entry stored with the dir_entry merely
	 * supplies the name of the directory (up to dir_entry.namelen). We
	 * track the number of 'active' files in a directory in dir_entry.nr,
	 * so we can tell if the directory is still relevant, e.g. for git
	 * status. However, if cache_entries are removed, we cannot pinpoint
	 * an exact cache_entry that's still active. It is very possible that
	 * multiple dir_entries point to the same cache_entry.
	 */
	struct dir_entry *dir;

	/* get length of parent directory */
	while (namelen > 0 && !is_dir_sep(ce->name[namelen - 1]))
		namelen--;
	if (namelen <= 0)
		return NULL;
	namelen--;

	/* lookup existing entry for that directory */
	dir = find_dir_entry(istate, ce->name, namelen);
	if (!dir) {
		/* not found, create it and add to hash table */
		dir = xcalloc(1, sizeof(struct dir_entry));
		hashmap_entry_init(dir, memihash(ce->name, namelen));
		dir->namelen = namelen;
		dir->ce = ce;
		hashmap_add(&istate->dir_hash, dir);

		/* recursively add missing parent directories */
		dir->parent = hash_dir_entry(istate, ce, namelen);
	}
	return dir;
}
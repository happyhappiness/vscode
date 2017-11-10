static struct dir_entry *hash_dir_entry_with_parent_and_prefix(
	struct index_state *istate,
	struct dir_entry *parent,
	struct strbuf *prefix)
{
	struct dir_entry *dir;
	unsigned int hash;
	int lock_nr;

	/*
	 * Either we have a parent directory and path with slash(es)
	 * or the directory is an immediate child of the root directory.
	 */
	assert((parent != NULL) ^ (strchr(prefix->buf, '/') == NULL));

	if (parent)
		hash = memihash_cont(parent->ent.hash,
			prefix->buf + parent->namelen,
			prefix->len - parent->namelen);
	else
		hash = memihash(prefix->buf, prefix->len);

	lock_nr = compute_dir_lock_nr(&istate->dir_hash, hash);
	lock_dir_mutex(lock_nr);

	dir = find_dir_entry__hash(istate, prefix->buf, prefix->len, hash);
	if (!dir) {
		FLEX_ALLOC_MEM(dir, name, prefix->buf, prefix->len);
		hashmap_entry_init(dir, hash);
		dir->namelen = prefix->len;
		dir->parent = parent;
		hashmap_add(&istate->dir_hash, dir);

		if (parent) {
			unlock_dir_mutex(lock_nr);

			/* All I really need here is an InterlockedIncrement(&(parent->nr)) */
			lock_nr = compute_dir_lock_nr(&istate->dir_hash, parent->ent.hash);
			lock_dir_mutex(lock_nr);
			parent->nr++;
		}
	}

	unlock_dir_mutex(lock_nr);

	return dir;
}
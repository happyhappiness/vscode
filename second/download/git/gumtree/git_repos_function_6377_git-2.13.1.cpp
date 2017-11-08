struct ref_dir *get_ref_dir(struct ref_entry *entry)
{
	struct ref_dir *dir;
	assert(entry->flag & REF_DIR);
	dir = &entry->u.subdir;
	if (entry->flag & REF_INCOMPLETE) {
		if (!dir->cache->fill_ref_dir)
			die("BUG: incomplete ref_store without fill_ref_dir function");

		dir->cache->fill_ref_dir(dir->cache->ref_store, dir, entry->name);
		entry->flag &= ~REF_INCOMPLETE;
	}
	return dir;
}
static struct ref_dir *search_for_subdir(struct ref_dir *dir,
					 const char *subdirname, size_t len,
					 int mkdir)
{
	int entry_index = search_ref_dir(dir, subdirname, len);
	struct ref_entry *entry;
	if (entry_index == -1) {
		if (!mkdir)
			return NULL;
		/*
		 * Since dir is complete, the absence of a subdir
		 * means that the subdir really doesn't exist;
		 * therefore, create an empty record for it but mark
		 * the record complete.
		 */
		entry = create_dir_entry(dir->cache, subdirname, len, 0);
		add_entry_to_dir(dir, entry);
	} else {
		entry = dir->entries[entry_index];
	}
	return get_ref_dir(entry);
}
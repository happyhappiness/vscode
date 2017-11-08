static void prime_ref_dir(struct ref_dir *dir)
{
	/*
	 * The hard work of loading loose refs is done by get_ref_dir(), so we
	 * just need to recurse through all of the sub-directories. We do not
	 * even need to care about sorting, as traversal order does not matter
	 * to us.
	 */
	int i;
	for (i = 0; i < dir->nr; i++) {
		struct ref_entry *entry = dir->entries[i];
		if (entry->flag & REF_DIR)
			prime_ref_dir(get_ref_dir(entry));
	}
}
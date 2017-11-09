static void prime_ref_dir(struct ref_dir *dir, const char *prefix)
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
		if (!(entry->flag & REF_DIR)) {
			/* Not a directory; no need to recurse. */
		} else if (!prefix) {
			/* Recurse in any case: */
			prime_ref_dir(get_ref_dir(entry), NULL);
		} else {
			switch (overlaps_prefix(entry->name, prefix)) {
			case PREFIX_CONTAINS_DIR:
				/*
				 * Recurse, and from here down we
				 * don't have to check the prefix
				 * anymore:
				 */
				prime_ref_dir(get_ref_dir(entry), NULL);
				break;
			case PREFIX_WITHIN_DIR:
				prime_ref_dir(get_ref_dir(entry), prefix);
				break;
			case PREFIX_EXCLUDES_DIR:
				/* No need to prime this directory. */
				break;
			}
		}
	}
}
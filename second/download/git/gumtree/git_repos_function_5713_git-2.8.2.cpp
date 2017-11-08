static void free_ref_entry(struct ref_entry *entry)
{
	if (entry->flag & REF_DIR) {
		/*
		 * Do not use get_ref_dir() here, as that might
		 * trigger the reading of loose refs.
		 */
		clear_ref_dir(&entry->u.subdir);
	}
	free(entry);
}
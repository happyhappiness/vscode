{
	struct mtree_writer *mtree= a->format_data;
	struct mtree_entry *mtree_entry;
	int r, r2;

	if (mtree->first) {
		mtree->first = 0;
		archive_strcat(&mtree->buf, "#mtree\n");
		if ((mtree->keys & SET_KEYS) == 0)
			mtree->output_global_set = 0;/* Disabled. */
	}

	mtree->entry_bytes_remaining = archive_entry_size(entry);

	/* While directory only mode, we do not handle non directory files. */
	if (mtree->dironly && archive_entry_filetype(entry) != AE_IFDIR)
		return (ARCHIVE_OK);

	r2 = mtree_entry_new(a, entry, &mtree_entry);
	if (r2 < ARCHIVE_WARN)
		return (r2);
	r = mtree_entry_tree_add(a, &mtree_entry);
	if (r < ARCHIVE_WARN) {
		mtree_entry_free(mtree_entry);
		return (r);
	}
	mtree->mtree_entry = mtree_entry;

	/* If the current file is a regular file, we have to
	 * compute the sum of its content.
	 * Initialize a bunch of sum check context. */
	if (mtree_entry->reg_info)
		sum_init(mtree);

	return (r2);
}
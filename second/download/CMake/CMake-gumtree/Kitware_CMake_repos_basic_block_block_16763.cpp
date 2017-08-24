{
	struct mtree_writer *mtree= a->format_data;

	if (n > mtree->entry_bytes_remaining)
		n = (size_t)mtree->entry_bytes_remaining;
	mtree->entry_bytes_remaining -= n;

	/* We don't need to compute a regular file sum */
	if (mtree->mtree_entry == NULL)
		return (n);

	if (mtree->mtree_entry->filetype == AE_IFREG)
		sum_update(mtree, buff, n);

	return (n);
}
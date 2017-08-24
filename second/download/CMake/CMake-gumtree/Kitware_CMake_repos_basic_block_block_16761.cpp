{
	struct mtree_writer *mtree= a->format_data;
	int ret;

	if (mtree->root != NULL) {
		ret = write_mtree_entry_tree(a);
		if (ret != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
	}

	archive_write_set_bytes_in_last_block(&a->archive, 1);

	return __archive_write_output(a, mtree->buf.s, mtree->buf.length);
}
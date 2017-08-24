{
	struct mtree_writer *mtree= a->format_data;

	if (mtree == NULL)
		return (ARCHIVE_OK);

	/* Make sure we dot not leave any entries. */
	mtree_entry_register_free(mtree);
	archive_string_free(&mtree->cur_dirstr);
	archive_string_free(&mtree->ebuf);
	archive_string_free(&mtree->buf);
	attr_counter_set_free(mtree);
	free(mtree);
	a->format_data = NULL;
	return (ARCHIVE_OK);
}
{
	int64_t bytes_skipped;
	int64_t request;
	struct sparse_block *p;
	struct tar* tar;

	tar = (struct tar *)(a->format->data);

	/* Do not consume the hole of a sparse file. */
	request = 0;
	for (p = tar->sparse_list; p != NULL; p = p->next) {
		if (!p->hole) {
			if (p->remaining >= INT64_MAX - request) {
				return ARCHIVE_FATAL;
			}
			request += p->remaining;
		}
	}
	if (request > tar->entry_bytes_remaining)
		request = tar->entry_bytes_remaining;
	request += tar->entry_padding + tar->entry_bytes_unconsumed;

	bytes_skipped = __archive_read_consume(a, request);
	if (bytes_skipped < 0)
		return (ARCHIVE_FATAL);

	tar->entry_bytes_remaining = 0;
	tar->entry_bytes_unconsumed = 0;
	tar->entry_padding = 0;

	/* Free the sparse list. */
	gnu_clear_sparse_list(tar);

	return (ARCHIVE_OK);
}
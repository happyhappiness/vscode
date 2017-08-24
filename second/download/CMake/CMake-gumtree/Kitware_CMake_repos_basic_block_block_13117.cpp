{
	struct xar *xar;
	int64_t bytes_skipped;

	xar = (struct xar *)(a->format->data);
	if (xar->end_of_file)
		return (ARCHIVE_EOF);
	bytes_skipped = __archive_read_consume(a, xar->entry_remaining +
		xar->entry_unconsumed);
	if (bytes_skipped < 0)
		return (ARCHIVE_FATAL);
	xar->offset += bytes_skipped;
	xar->entry_unconsumed = 0;
	return (ARCHIVE_OK);
}
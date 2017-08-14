static int
gnu_sparse_old_read(struct archive_read *a, struct tar *tar,
    const struct archive_entry_header_gnutar *header, size_t *unconsumed)
{
	ssize_t bytes_read;
	const void *data;
	struct extended {
		struct gnu_sparse sparse[21];
		char	isextended[1];
		char	padding[7];
	};
	const struct extended *ext;

	if (gnu_sparse_old_parse(a, tar, header->sparse, 4) != ARCHIVE_OK)
		return (ARCHIVE_FATAL);
	if (header->isextended[0] == 0)
		return (ARCHIVE_OK);

	do {
		tar_flush_unconsumed(a, unconsumed);
		data = __archive_read_ahead(a, 512, &bytes_read);
		if (bytes_read < 0)
			return (ARCHIVE_FATAL);
		if (bytes_read < 512) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
			    "Truncated tar archive "
			    "detected while reading sparse file data");
			return (ARCHIVE_FATAL);
		}
		*unconsumed = 512;
		ext = (const struct extended *)data;
		if (gnu_sparse_old_parse(a, tar, ext->sparse, 21) != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
	} while (ext->isextended[0] != 0);
	if (tar->sparse_list != NULL)
		tar->entry_offset = tar->sparse_list->offset;
	return (ARCHIVE_OK);
}
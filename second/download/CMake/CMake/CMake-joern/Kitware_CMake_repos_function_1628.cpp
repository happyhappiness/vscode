static int
gnu_add_sparse_entry(struct archive_read *a, struct tar *tar,
    int64_t offset, int64_t remaining)
{
	struct sparse_block *p;

	p = (struct sparse_block *)calloc(1, sizeof(*p));
	if (p == NULL) {
		archive_set_error(&a->archive, ENOMEM, "Out of memory");
		return (ARCHIVE_FATAL);
	}
	if (tar->sparse_last != NULL)
		tar->sparse_last->next = p;
	else
		tar->sparse_list = p;
	tar->sparse_last = p;
	if (remaining < 0 || offset < 0) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC, "Malformed sparse map data");
		return (ARCHIVE_FATAL);
	}
	p->offset = offset;
	p->remaining = remaining;
	return (ARCHIVE_OK);
}
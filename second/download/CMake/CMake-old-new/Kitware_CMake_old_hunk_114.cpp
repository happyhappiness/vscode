{
	struct sparse_block *p;

	p = (struct sparse_block *)malloc(sizeof(*p));
	if (p == NULL) {
		archive_set_error(&a->archive, ENOMEM, "Out of memory");
		return (ARCHIVE_FATAL);
	}
	memset(p, 0, sizeof(*p));
	if (tar->sparse_last != NULL)
		tar->sparse_last->next = p;
	else

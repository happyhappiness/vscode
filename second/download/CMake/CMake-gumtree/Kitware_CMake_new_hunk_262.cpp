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


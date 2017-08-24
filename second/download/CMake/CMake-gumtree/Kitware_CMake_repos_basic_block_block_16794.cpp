{
	struct archive_write *a = (struct archive_write *)_a;
	struct mtree_writer *mtree;

	archive_check_magic(_a, ARCHIVE_WRITE_MAGIC, ARCHIVE_STATE_NEW, fn);

	if (a->format_free != NULL)
		(a->format_free)(a);

	if ((mtree = calloc(1, sizeof(*mtree))) == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate mtree data");
		return (ARCHIVE_FATAL);
	}

	mtree->mtree_entry = NULL;
	mtree->first = 1;
	memset(&(mtree->set), 0, sizeof(mtree->set));
	mtree->keys = DEFAULT_KEYS;
	mtree->dironly = 0;
	mtree->indent = 0;
	archive_string_init(&mtree->ebuf);
	archive_string_init(&mtree->buf);
	mtree_entry_register_init(mtree);
	a->format_data = mtree;
	a->format_free = archive_write_mtree_free;
	a->format_name = "mtree";
	a->format_options = archive_write_mtree_options;
	a->format_write_header = archive_write_mtree_header;
	a->format_close = archive_write_mtree_close;
	a->format_write_data = archive_write_mtree_data;
	a->format_finish_entry = archive_write_mtree_finish_entry;
	a->archive.archive_format = ARCHIVE_FORMAT_MTREE;
	a->archive.archive_format_name = "mtree";

	return (ARCHIVE_OK);
}
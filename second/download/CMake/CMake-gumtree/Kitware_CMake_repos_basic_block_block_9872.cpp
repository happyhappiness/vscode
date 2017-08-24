{
	struct archive_read_disk *a = (struct archive_read_disk *)_a;
	int r;

	if (_a == NULL)
		return (ARCHIVE_OK);
	archive_check_magic(_a, ARCHIVE_READ_DISK_MAGIC,
	    ARCHIVE_STATE_ANY | ARCHIVE_STATE_FATAL, "archive_read_free");

	if (a->archive.state != ARCHIVE_STATE_CLOSED)
		r = _archive_read_close(&a->archive);
	else
		r = ARCHIVE_OK;

	tree_free(a->tree);
	if (a->cleanup_gname != NULL && a->lookup_gname_data != NULL)
		(a->cleanup_gname)(a->lookup_gname_data);
	if (a->cleanup_uname != NULL && a->lookup_uname_data != NULL)
		(a->cleanup_uname)(a->lookup_uname_data);
	archive_string_free(&a->archive.error_string);
	archive_entry_free(a->entry);
	a->archive.magic = 0;
	free(a);
	return (r);
}
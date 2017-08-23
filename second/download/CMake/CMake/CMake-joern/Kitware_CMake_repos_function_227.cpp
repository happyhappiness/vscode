static int
mtree_entry_create_virtual_dir(struct archive_write *a, const char *pathname,
    struct mtree_entry **m_entry)
{
	struct archive_entry *entry;
	struct mtree_entry *file;
	int r;

	entry = archive_entry_new();
	if (entry == NULL) {
		*m_entry = NULL;
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate memory");
		return (ARCHIVE_FATAL);
	}
	archive_entry_copy_pathname(entry, pathname);
	archive_entry_set_mode(entry, AE_IFDIR | 0755);
	archive_entry_set_mtime(entry, time(NULL), 0);

	r = mtree_entry_new(a, entry, &file);
	archive_entry_free(entry);
	if (r < ARCHIVE_WARN) {
		*m_entry = NULL;
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate memory");
		return (ARCHIVE_FATAL);
	}

	file->dir_info->virtual = 1;

	*m_entry = file;
	return (ARCHIVE_OK);
}
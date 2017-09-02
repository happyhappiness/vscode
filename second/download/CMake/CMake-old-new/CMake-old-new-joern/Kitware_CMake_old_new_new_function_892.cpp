static int
_archive_read_disk_open_w(struct archive *_a, const wchar_t *pathname)
{
	struct archive_read_disk *a = (struct archive_read_disk *)_a;

	if (a->tree != NULL)
		a->tree = tree_reopen(a->tree, pathname, a->restore_time);
	else
		a->tree = tree_open(pathname, a->symlink_mode, a->restore_time);
	if (a->tree == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate directory traversal data");
		a->archive.state = ARCHIVE_STATE_FATAL;
		return (ARCHIVE_FATAL);
	}
	a->archive.state = ARCHIVE_STATE_HEADER;

	return (ARCHIVE_OK);
}
int
archive_read_disk_open_w(struct archive *_a, const wchar_t *pathname)
{
	struct archive_read_disk *a = (struct archive_read_disk *)_a;
	struct archive_string path;
	int ret;

	archive_check_magic(_a, ARCHIVE_READ_DISK_MAGIC,
	    ARCHIVE_STATE_NEW | ARCHIVE_STATE_CLOSED,
	    "archive_read_disk_open_w");
	archive_clear_error(&a->archive);

	/* Make a char string from a wchar_t string. */
	archive_string_init(&path);
	if (archive_string_append_from_wcs(&path, pathname,
	    wcslen(pathname)) != 0) {
		if (errno == ENOMEM)
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory");
		else
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Can't convert a path to a char string");
		a->archive.state = ARCHIVE_STATE_FATAL;
		ret = ARCHIVE_FATAL;
	} else
		ret = _archive_read_disk_open(_a, path.s);

	archive_string_free(&path);
	return (ret);
}
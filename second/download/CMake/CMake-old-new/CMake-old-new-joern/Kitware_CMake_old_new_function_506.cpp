int
archive_read_disk_open(struct archive *_a, const char *pathname)
{
	struct archive_read_disk *a = (struct archive_read_disk *)_a;
	struct archive_wstring wpath;
	int ret;

	archive_check_magic(_a, ARCHIVE_READ_DISK_MAGIC,
	    ARCHIVE_STATE_NEW | ARCHIVE_STATE_CLOSED,
	    "archive_read_disk_open");
	archive_clear_error(&a->archive);

	/* Make a wchar_t string from a char string. */
	archive_string_init(&wpath);
	if (archive_wstring_append_from_mbs(&wpath, pathname,
	    strlen(pathname)) != 0) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Can't convert a path to a wchar_t string");
		a->archive.state = ARCHIVE_STATE_FATAL;
		ret = ARCHIVE_FATAL;
	} else
		ret = _archive_read_disk_open_w(_a, wpath.s);

	archive_wstring_free(&wpath);
	return (ret);
}
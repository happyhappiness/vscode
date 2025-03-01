static int
open_filename(struct archive *a, int mbs_fn, const void *filename)
{
	struct write_file_data *mine;
	int r;

	mine = (struct write_file_data *)calloc(1, sizeof(*mine));
	if (mine == NULL) {
		archive_set_error(a, ENOMEM, "No memory");
		return (ARCHIVE_FATAL);
	}
	if (mbs_fn)
		r = archive_mstring_copy_mbs(&mine->filename, filename);
	else
		r = archive_mstring_copy_wcs(&mine->filename, filename);
	if (r < 0) {
		if (errno == ENOMEM) {
			archive_set_error(a, ENOMEM, "No memory");
			return (ARCHIVE_FATAL);
		}
		if (mbs_fn)
			archive_set_error(a, ARCHIVE_ERRNO_MISC,
			    "Can't convert '%s' to WCS",
			    (const char *)filename);
		else
			archive_set_error(a, ARCHIVE_ERRNO_MISC,
			    "Can't convert '%S' to MBS",
			    (const wchar_t *)filename);
		return (ARCHIVE_FAILED);
	}
	mine->fd = -1;
	return (archive_write_open(a, mine,
		file_open, file_write, file_close));
}
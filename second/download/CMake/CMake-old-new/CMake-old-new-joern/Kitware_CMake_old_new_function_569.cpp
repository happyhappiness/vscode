int
archive_read_open_filename_w(struct archive *a, const wchar_t *wfilename,
    size_t block_size)
{
	enum fnt_e filename_type;

	if (wfilename == NULL || wfilename[0] == L'\0') {
		filename_type = FNT_STDIN;
	} else {
#if defined(_WIN32) && !defined(__CYGWIN__)
		filename_type = FNT_WCS;
#else
		/*
		 * POSIX system does not support a wchar_t interface for
		 * open() system call, so we have to translate a whcar_t
		 * filename to multi-byte one and use it.
		 */
		struct archive_string fn;
		int r;

		archive_string_init(&fn);
		if (archive_string_append_from_wcs(&fn, wfilename,
		    wcslen(wfilename)) != 0) {
			archive_set_error(a, EINVAL,
			    "Failed to convert a wide-character filename to"
			    " a multi-byte filename");
			archive_string_free(&fn);
			return (ARCHIVE_FATAL);
		}
		r = file_open_filename(a, FNT_MBS, fn.s, block_size);
		archive_string_free(&fn);
		return (r);
#endif
	}
	return (file_open_filename(a, filename_type, wfilename, block_size));
}
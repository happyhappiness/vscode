		setmode(0, O_BINARY);

#endif

		filename = "";

	} else if (filename_type == FNT_MBS) {

		filename = (const char *)_filename;

		fd = open(filename, O_RDONLY | O_BINARY);

		if (fd < 0) {

			archive_set_error(a, errno,

			    "Failed to open '%s'", filename);

			return (ARCHIVE_FATAL);

		}

	} else {

#if defined(_WIN32) && !defined(__CYGWIN__)

		wfilename = (const wchar_t *)_filename;

		fd = _wopen(wfilename, O_RDONLY | O_BINARY);

		if (fd < 0 && errno == ENOENT) {

			wchar_t *fullpath;


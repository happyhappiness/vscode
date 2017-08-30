#else

		archive_set_error(a, ARCHIVE_ERRNO_MISC,

		    "Unexpedted operation in archive_read_open_filename");

		return (ARCHIVE_FATAL);

#endif

	}

	if (fstat(fd, &st) != 0) {


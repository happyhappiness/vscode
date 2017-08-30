		return (r);

	if ((size_t)r < size) {

		archive_set_error(&a->archive, 0,

		    "Too much data: Truncating file at %ju bytes", (uintmax_t)a->filesize);

		return (ARCHIVE_WARN);

	}

#if ARCHIVE_VERSION_NUMBER < 3999000


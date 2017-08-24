(rsrc->uncompressed_size > (4 * 1024 * 1024)) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Mac metadata is too large: %jd > 4M bytes",
		    (intmax_t)rsrc->uncompressed_size);
		return (ARCHIVE_WARN);
	}
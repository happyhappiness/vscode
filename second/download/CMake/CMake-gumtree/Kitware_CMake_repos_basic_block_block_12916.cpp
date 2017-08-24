do {
		tar_flush_unconsumed(a, unconsumed);
		data = __archive_read_ahead(a, 512, &bytes_read);
		if (bytes_read < 0)
			return (ARCHIVE_FATAL);
		if (bytes_read < 512) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
			    "Truncated tar archive "
			    "detected while reading sparse file data");
			return (ARCHIVE_FATAL);
		}
		*unconsumed = 512;
		ext = (const struct extended *)data;
		if (gnu_sparse_old_parse(a, tar, ext->sparse, 21) != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
	} while (ext->isextended[0] != 0);
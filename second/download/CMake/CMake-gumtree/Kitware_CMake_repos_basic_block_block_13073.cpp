(toc_chksum_alg != CKSUM_NONE) {
		r = move_reading_point(a, xar->toc_chksum_offset);
		if (r != ARCHIVE_OK)
			return (r);
		b = __archive_read_ahead(a,
			(size_t)xar->toc_chksum_size, &bytes);
		if (bytes < 0)
			return ((int)bytes);
		if ((uint64_t)bytes < xar->toc_chksum_size) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Truncated archive file");
			return (ARCHIVE_FATAL);
		}
		r = checksum_final(a, b,
			(size_t)xar->toc_chksum_size, NULL, 0);
		__archive_read_consume(a, xar->toc_chksum_size);
		xar->offset += xar->toc_chksum_size;
		if (r != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
	}
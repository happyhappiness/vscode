(next_header_offset != 0) {
		if (bytes_avail >= (ssize_t)next_header_offset)
			__archive_read_consume(a, next_header_offset);
		else if (__archive_read_seek(a,
		    next_header_offset + zip->seek_base, SEEK_SET) < 0)
			return (ARCHIVE_FATAL);
	}
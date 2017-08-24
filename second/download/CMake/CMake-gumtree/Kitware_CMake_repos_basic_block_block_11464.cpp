{
		*buff = __archive_read_ahead(a, 1, &bytes_read);
		if (bytes_read <= 0)
			return (ARCHIVE_FATAL);
		if (bytes_read > cpio->entry_bytes_remaining)
			bytes_read = (ssize_t)cpio->entry_bytes_remaining;
		*size = bytes_read;
		cpio->entry_bytes_unconsumed = bytes_read;
		*offset = cpio->entry_offset;
		cpio->entry_offset += bytes_read;
		cpio->entry_bytes_remaining -= bytes_read;
		return (ARCHIVE_OK);
	}
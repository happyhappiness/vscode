{
		if (cpio->entry_padding !=
			__archive_read_consume(a, cpio->entry_padding)) {
			return (ARCHIVE_FATAL);
		}
		cpio->entry_padding = 0;
		*buff = NULL;
		*size = 0;
		*offset = cpio->entry_offset;
		return (ARCHIVE_EOF);
	}
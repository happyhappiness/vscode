{
		__archive_read_consume(a, cpio->entry_bytes_unconsumed);
		cpio->entry_bytes_unconsumed = 0;
	}
{
		__archive_read_consume(a, ar->entry_bytes_unconsumed);
		ar->entry_bytes_unconsumed = 0;
	}
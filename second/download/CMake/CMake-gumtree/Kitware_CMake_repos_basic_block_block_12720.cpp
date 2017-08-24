{
			__archive_read_consume(a, tar->entry_bytes_unconsumed);
			tar->entry_bytes_unconsumed = 0;
		}
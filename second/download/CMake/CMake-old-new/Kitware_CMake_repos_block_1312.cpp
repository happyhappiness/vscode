{
					archive_set_error(
					    &a->archive, ENOMEM,
					    "No memory for multi extent");
					__archive_read_consume(a, skip_size);
					return (ARCHIVE_FATAL);
				}
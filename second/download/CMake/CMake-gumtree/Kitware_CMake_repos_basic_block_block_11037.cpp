{
		/*
		 * We are now at the beginning of the archive,
		 * so we need first consume the ar global header.
		 */
		__archive_read_consume(a, 8);
		ar->read_global_header = 1;
		/* Set a default format code for now. */
		a->archive.archive_format = ARCHIVE_FORMAT_AR;
	}
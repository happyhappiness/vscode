(archive_string_ensure(&mtree->line,
			total_size + bytes_read + 1) == NULL) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate working buffer");
			return (ARCHIVE_FATAL);
		}
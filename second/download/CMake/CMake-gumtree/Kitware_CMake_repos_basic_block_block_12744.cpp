{
		tar_flush_unconsumed(a, unconsumed);

		/* Read 512-byte header record */
		h = __archive_read_ahead(a, 512, &bytes);
		if (bytes < 0)
			return ((int)bytes);
		if (bytes == 0) { /* EOF at a block boundary. */
			/* Some writers do omit the block of nulls. <sigh> */
			return (ARCHIVE_EOF);
		}
		if (bytes < 512) {  /* Short block at EOF; this is bad. */
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Truncated tar archive");
			return (ARCHIVE_FATAL);
		}
		*unconsumed = 512;

		/* Header is workable if it's not an end-of-archive mark. */
		if (h[0] != 0 || !archive_block_is_null(h))
			break;

		/* Ensure format is set for archives with only null blocks. */
		if (a->archive.archive_format_name == NULL) {
			a->archive.archive_format = ARCHIVE_FORMAT_TAR;
			a->archive.archive_format_name = "tar";
		}

		if (!tar->read_concatenated_archives) {
			/* Try to consume a second all-null record, as well. */
			tar_flush_unconsumed(a, unconsumed);
			h = __archive_read_ahead(a, 512, NULL);
			if (h != NULL && h[0] == 0 && archive_block_is_null(h))
				__archive_read_consume(a, 512);
			archive_clear_error(&a->archive);
			return (ARCHIVE_EOF);
		}

		/*
		 * We're reading concatenated archives, ignore this block and
		 * loop to get the next.
		 */
	}
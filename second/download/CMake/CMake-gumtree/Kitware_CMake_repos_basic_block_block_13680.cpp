{
		/* We know the compressed length, so we can just skip. */
		bytes_skipped = __archive_read_consume(a,
					zip->entry_bytes_remaining);
		if (bytes_skipped < 0)
			return (ARCHIVE_FATAL);
		return (ARCHIVE_OK);
	}
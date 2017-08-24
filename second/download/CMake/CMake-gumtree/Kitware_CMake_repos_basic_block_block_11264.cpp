{
		cab->bytes_skipped += cab->entry_bytes_remaining;
		cab->entry_bytes_remaining = 0;
		/* This entry is finished and done. */
		cab->end_of_entry_cleanup = cab->end_of_entry = 1;
		return (ARCHIVE_OK);
	}
{
		int64_t offset, length, last_offset = 0;
		/* Get the last entry of sparse block. */
		while (archive_entry_sparse_next(
		    entry_main, &offset, &length) == ARCHIVE_OK)
			last_offset = offset + length;

		/* If the last sparse block does not reach the end of file,
		 * We have to add a empty sparse block as the last entry to
		 * manage storing file data. */
		if (last_offset < archive_entry_size(entry_main))
			archive_entry_sparse_add_entry(entry_main,
			    archive_entry_size(entry_main), 0);
		sparse_count = archive_entry_sparse_reset(entry_main);
	}
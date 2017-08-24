(archive_entry_size(file->entry) <= LOGICAL_BLOCK_SIZE)
		return (ARCHIVE_OK);
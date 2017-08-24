{
		/* Set the size only if it's meaningful. */
		archive_entry_set_size(entry, zip_entry->uncompressed_size);
	}
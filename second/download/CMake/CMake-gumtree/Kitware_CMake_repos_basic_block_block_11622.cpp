{
		/* Overwrite nlinks by proper link number which is
		 * calculated from number of sub directories. */
		archive_entry_set_nlink(entry, 2 + file->subdirs);
		/* Directory data has been read completely. */
		iso9660->entry_bytes_remaining = 0;
	}
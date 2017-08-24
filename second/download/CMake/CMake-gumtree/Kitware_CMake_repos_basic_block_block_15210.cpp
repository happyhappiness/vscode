{
		/* If we're not overwriting, we're done. */
		archive_entry_unset_size(a->entry);
		return (ARCHIVE_OK);
	}
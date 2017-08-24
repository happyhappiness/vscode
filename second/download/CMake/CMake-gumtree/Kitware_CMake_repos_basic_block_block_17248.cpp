(archive_entry_hardlink(entry) != NULL ||
	    archive_entry_symlink(entry) != NULL ||
	    !(archive_entry_filetype(entry) == AE_IFREG))
		archive_entry_set_size(entry, 0)
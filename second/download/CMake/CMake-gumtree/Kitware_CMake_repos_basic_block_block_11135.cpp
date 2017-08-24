(file->attr & ATTR_RDONLY)
		archive_entry_set_mode(entry, AE_IFREG | 0555);
	else
		archive_entry_set_mode(entry, AE_IFREG | 0666)
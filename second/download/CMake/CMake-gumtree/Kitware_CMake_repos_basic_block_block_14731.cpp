(a->fd < 0) {
		archive_entry_set_size(entry, 0);
		a->filesize = 0;
	}
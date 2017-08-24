(r != ARCHIVE_OK) {
		archive_copy_error(&(a->archive), ar);
		archive_read_free(ar);
		return (r);
	}
{
		archive_set_error(&a->archive, -1, "Damaged Zip archive");
		return ARCHIVE_FATAL;
	}
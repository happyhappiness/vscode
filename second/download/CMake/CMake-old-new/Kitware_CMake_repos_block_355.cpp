{
		archive_set_error(&a->archive, errno,
				  "Failed to restore metadata");
		archive_string_free(&tmp);
		return (ARCHIVE_WARN);
	}
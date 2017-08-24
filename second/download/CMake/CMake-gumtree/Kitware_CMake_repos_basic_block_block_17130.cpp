(archive_string_ensure(&shar->work, ensured + 3) == NULL) {
		archive_set_error(&a->archive, ENOMEM, "Out of memory");
		return (ARCHIVE_FATAL);
	}
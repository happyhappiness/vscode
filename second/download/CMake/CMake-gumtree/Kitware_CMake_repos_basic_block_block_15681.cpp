{
	const char *path;
	size_t len;

	if (archive_entry_filetype(entry) == 0) {
		archive_set_error(&a->archive, -1, "Filetype required");
		return (ARCHIVE_FAILED);
	}

	if (archive_entry_pathname_l(entry, &path, &len, get_sconv(a)) != 0
	    && errno == ENOMEM) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate memory for Pathname");
		return (ARCHIVE_FATAL);
	}
	if (len == 0 || path == NULL || path[0] == '\0') {
		archive_set_error(&a->archive, -1, "Pathname required");
		return (ARCHIVE_FAILED);
	}

	if (archive_entry_hardlink(entry) == NULL
	    && (!archive_entry_size_is_set(entry) || archive_entry_size(entry) < 0)) {
		archive_set_error(&a->archive, -1, "Size required");
		return (ARCHIVE_FAILED);
	}
	return write_header(a, entry);
}
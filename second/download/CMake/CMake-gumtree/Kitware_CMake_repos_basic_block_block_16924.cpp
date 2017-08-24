{
	int r;

	r = archive_entry_gname_l(entry, name, length, sc);
	if (r != 0) {
		if (errno == ENOMEM) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for Gname");
			return (ARCHIVE_FATAL);
		}
		return (ARCHIVE_WARN);
	}
	return (ARCHIVE_OK);
}
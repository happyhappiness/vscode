{
	if (errno == ENOMEM) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate memory for %s", name);
		return (ARCHIVE_FATAL);
	}
	archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
	    "%s can't be converted from %s to current locale.",
	    name, archive_string_conversion_charset_name(sconv));
	return (ARCHIVE_WARN);
}
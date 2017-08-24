(0 > archive_entry_pathname_l(entry, &u16, &u16len, zip->sconv)) {
		if (errno == ENOMEM) {
			free(file);
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for UTF-16LE");
			return (ARCHIVE_FATAL);
		}
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "A filename cannot be converted to UTF-16LE;"
		    "You should disable making Joliet extension");
		ret = ARCHIVE_WARN;
	}
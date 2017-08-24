(archive_entry_pathname_l(entry, &path, &len, get_sconv(a)) != 0
	    && errno == ENOMEM) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate memory for Pathname");
		return (ARCHIVE_FATAL);
	}
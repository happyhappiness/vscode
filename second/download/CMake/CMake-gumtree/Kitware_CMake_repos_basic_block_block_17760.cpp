(archive_random(key, sizeof(key)-1) != ARCHIVE_OK) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Can't generate random number for encryption");
		return ARCHIVE_FATAL;
	}
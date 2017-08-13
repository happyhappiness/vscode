{
		if (r == ARCHIVE_FATAL) {
			archive_set_error(&a->archive, ENOMEM,
			    "%s %s", "Can't allocate memory for ",
			    errstr);
			return (r);
		}
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_MISC, "%s %s", "Parse error: ", errstr);
	}
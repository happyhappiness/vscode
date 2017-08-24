(err != ARCHIVE_OK) {
		if (errno == ENOMEM) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for ACL");
		} else
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Malformed Solaris ACL attribute (unparsable)");
	}
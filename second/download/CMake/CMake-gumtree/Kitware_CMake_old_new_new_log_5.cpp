archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Cannot restore extended attributes: %s",
			    errlist.s);
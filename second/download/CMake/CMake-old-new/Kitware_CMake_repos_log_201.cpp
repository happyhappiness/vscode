archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Internal programing error "
		    "in generating canonical name for %s",
		    file->pathname.s);
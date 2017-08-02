archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "%s: unknown encryption '%s'",
			    a->format_name, val)
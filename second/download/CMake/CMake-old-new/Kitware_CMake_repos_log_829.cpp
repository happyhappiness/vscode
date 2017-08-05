archive_set_error(&(a->archive),
					ARCHIVE_ERRNO_MISC,
					"The %s is encrypted, "
					"but currently not supported", cname);
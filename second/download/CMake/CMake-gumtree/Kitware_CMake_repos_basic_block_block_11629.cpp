(errno == ENOMEM) {
					archive_set_error(&a->archive, ENOMEM,
					    "No memory for Linkname");
					return (ARCHIVE_FATAL);
				}
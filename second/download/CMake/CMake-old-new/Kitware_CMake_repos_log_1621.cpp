archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Unsupported CAB compression : %s",
		    cab->entry_cffolder->compname)
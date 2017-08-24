{
		*buff = NULL;
		*size = 0;
		*offset = 0;
		if (bytes_avail == 0 &&
		    cab->entry_cfdata->uncompressed_size == 0) {
			/* All of CFDATA in a folder has been handled. */
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT, "Invalid CFDATA");
			return (ARCHIVE_FATAL);
		} else
			return ((int)bytes_avail);
	}
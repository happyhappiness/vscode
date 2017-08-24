{
		zip->temp_offset = 0;
		zip->temp_fd = __archive_mktemp(NULL);
		if (zip->temp_fd < 0) {
			archive_set_error(&a->archive, errno,
			    "Couldn't create temporary file");
			return (ARCHIVE_FATAL);
		}
	}
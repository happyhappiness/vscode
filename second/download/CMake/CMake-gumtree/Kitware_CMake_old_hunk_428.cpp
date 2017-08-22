		/* We're done with the regular data; get the filename and
		 * extra data. */
		__archive_read_consume(a, 46);
		if ((p = __archive_read_ahead(a, filename_length + extra_length, NULL))
		    == NULL) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
			    "Truncated ZIP file header");
			return ARCHIVE_FATAL;
		}

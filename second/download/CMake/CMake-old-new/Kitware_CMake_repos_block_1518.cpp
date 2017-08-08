{
			/* don't bother */
			archive_set_error(
				&a->archive,
				ARCHIVE_ERRNO_FILE_FORMAT,
				"cannot archive file");
			return (ARCHIVE_WARN);
		}
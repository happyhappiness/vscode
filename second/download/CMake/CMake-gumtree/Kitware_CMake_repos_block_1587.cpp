{  /* Short block at EOF; this is bad. */
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Truncated tar archive");
			return (ARCHIVE_FATAL);
		}
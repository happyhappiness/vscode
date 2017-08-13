{
			/* Can't support backward move. */
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Seek failed");
			return (ARCHIVE_FATAL);
		}
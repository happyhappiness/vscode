{
			/* Invalid sequence. This might happen when
			 * reading a malformed archive. */
			archive_set_error(&(a->archive),
			    ARCHIVE_ERRNO_MISC, "Malformed 7-Zip archive");
			return (ARCHIVE_FATAL);
		}
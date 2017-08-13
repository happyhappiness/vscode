{
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Can't initialize deflate decompression.");
			*avail = ARCHIVE_FATAL;
			return (NULL);
		}
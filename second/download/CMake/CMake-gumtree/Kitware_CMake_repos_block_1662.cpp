{
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Can't initialize LZX decompression.");
			*avail = ARCHIVE_FATAL;
			return (NULL);
		}
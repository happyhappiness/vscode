{
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Can't initialize zisofs decompression.");
			return (ARCHIVE_FATAL);
		}
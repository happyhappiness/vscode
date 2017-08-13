{
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Path is a drive name");
			return (ARCHIVE_FAILED);
		}
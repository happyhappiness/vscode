{
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			                  "Path is absolute");
			return (ARCHIVE_FAILED);
		}
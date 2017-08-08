{
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Truncated tar archive");
			return (ARCHIVE_FATAL);
		}
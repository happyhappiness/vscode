{
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_FILE_FORMAT,
				    "Illegal zisofs file body");
				return (ARCHIVE_FATAL);
			}
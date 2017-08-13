{
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Unrecognized GNU sparse file format");
				return (ARCHIVE_WARN);
			}
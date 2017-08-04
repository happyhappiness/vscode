{
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "LHa data CRC error");
				return (ARCHIVE_WARN);
			}
{
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Failed to decompress resource fork");
				return (ARCHIVE_WARN);
			}
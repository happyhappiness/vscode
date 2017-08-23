{
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_MISC,
			    "ZIP bad Authentication code");
			return (ARCHIVE_WARN);
		}
{
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Ignoring malformed pax extended attribute");
			return (ARCHIVE_WARN);
		}
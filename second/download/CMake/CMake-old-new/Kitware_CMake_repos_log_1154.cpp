archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Internal error initializing "
				    "compression library: "
				    "Invalid or unsupported options");
archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_FILE_FORMAT,
		    "Unknown encryption algorithm: %u", zip->alg_id)
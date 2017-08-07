archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Truncated Zip encrypted body: only %jd bytes available",
		    (intmax_t)zip->entry_bytes_remaining);
archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Crypto codec not supported yet (ID: 0x%lX)", zip->codec)
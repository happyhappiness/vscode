archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
			    "Extra data overflow: Need %d bytes but only found %d bytes",
			    (int)datasize, (int)(extra_length - offset))
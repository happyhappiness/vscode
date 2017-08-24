(ret != ARCHIVE_OK) {
		ret_final = ARCHIVE_FATAL;
		goto exit_write_header;
	}
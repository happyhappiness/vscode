{
		archive_set_error(&a->archive, ENOMEM,
		    "No memory for ino translation table");
		ret_final = ARCHIVE_FATAL;
		goto exit_write_header;
	}
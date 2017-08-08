{
		archive_set_error(&a->archive, ERANGE,
		    "File is too large for cpio format.");
		ret_final = ARCHIVE_FAILED;
		goto exit_write_header;
	}
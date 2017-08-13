{
		archive_set_error(&a->archive, ERANGE,
		    "Too many files for this cpio format");
		ret_final = ARCHIVE_FATAL;
		goto exit_write_header;
	}
{
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Truncated RAR file data");
		zip->ppstream.overconsumed = 1;
		return (0);
	}
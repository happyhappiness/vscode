(format_number(archive_entry_size(entry),
	    h + USTAR_size_offset, USTAR_size_size, USTAR_size_max_size, strict)) {
		archive_set_error(&a->archive, ERANGE,
		    "File size out of range");
		ret = ARCHIVE_FAILED;
	}
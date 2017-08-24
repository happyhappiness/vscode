(format_number(archive_entry_uid(entry),
	    h + V7TAR_uid_offset, V7TAR_uid_size, V7TAR_uid_max_size, strict)) {
		archive_set_error(&a->archive, ERANGE,
		    "Numeric user ID too large");
		ret = ARCHIVE_FAILED;
	}
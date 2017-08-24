(format_decimal(archive_entry_gid(entry), buff + AR_gid_offset, AR_gid_size)) {
		archive_set_error(&a->archive, ERANGE,
		    "Numeric group ID too large");
		return (ARCHIVE_WARN);
	}
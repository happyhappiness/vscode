{
		archive_entry_copy_pathname(entry, filename);
		/* Parse the time, owner, mode, size fields. */
		return (ar_parse_common_header(ar, entry, h));
	}
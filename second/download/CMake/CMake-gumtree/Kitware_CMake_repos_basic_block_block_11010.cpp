{
		archive_entry_copy_pathname(entry, "/");
		/* Parse the time, owner, mode, size fields. */
		r = ar_parse_common_header(ar, entry, h);
		/* Force the file type to a regular file. */
		archive_entry_set_filetype(entry, AE_IFREG);
		return (r);
	}
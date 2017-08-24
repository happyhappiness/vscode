(iso9660->opt.limit_dirs && dir_number > 0xffff) {
		/*
		 * Maximum number of directories is 65535(0xffff)
		 * doe to size(16bit) of Parent Directory Number of
		 * the Path Table.
		 * See also ISO9660 Standard 9.4.
		 */
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Too many directories(%d) over 65535.", dir_number);
		return (ARCHIVE_FATAL);
	}
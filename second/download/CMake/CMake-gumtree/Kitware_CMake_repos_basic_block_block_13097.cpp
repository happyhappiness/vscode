(file->symlink.length > 0 &&
	    archive_entry_copy_symlink_l(entry, file->symlink.s,
		archive_strlen(&(file->symlink)), xar->sconv) != 0) {
		if (errno == ENOMEM) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for Linkname");
			return (ARCHIVE_FATAL);
		}
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_FILE_FORMAT,
		    "Linkname cannot be converted from %s to current locale.",
		    archive_string_conversion_charset_name(xar->sconv));
		r = ARCHIVE_WARN;
	}
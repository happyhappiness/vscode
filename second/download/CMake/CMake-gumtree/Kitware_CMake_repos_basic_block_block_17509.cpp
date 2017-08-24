{
		size_t len2;
		/* Convert symlink name too. */
		if (archive_entry_symlink_l(file->entry, &pp, &len2,
		    xar->sconv) != 0) {
			if (errno == ENOMEM) {
				archive_set_error(&a->archive, ENOMEM,
				    "Can't allocate memory for Linkname");
				return (ARCHIVE_FATAL);
			}
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Can't translate symlink '%s' to UTF-8",
			    archive_entry_symlink(file->entry));
			r = ARCHIVE_WARN;
		}
		archive_strncpy(&(file->symlink), pp, len2);
		cleanup_backslash(file->symlink.s, file->symlink.length);
	}
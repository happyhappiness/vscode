{
		if (cpio->entry_bytes_remaining > 1024 * 1024) {
			archive_set_error(&a->archive, ENOMEM,
			    "Rejecting malformed cpio archive: symlink contents exceed 1 megabyte");
			return (ARCHIVE_FATAL);
		}
		hl = __archive_read_ahead(a,
			(size_t)cpio->entry_bytes_remaining, NULL);
		if (hl == NULL)
			return (ARCHIVE_FATAL);
		if (archive_entry_copy_symlink_l(entry, (const char *)hl,
		    (size_t)cpio->entry_bytes_remaining, sconv) != 0) {
			if (errno == ENOMEM) {
				archive_set_error(&a->archive, ENOMEM,
				    "Can't allocate memory for Linkname");
				return (ARCHIVE_FATAL);
			}
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Linkname can't be converted from %s to "
			    "current locale.",
			    archive_string_conversion_charset_name(sconv));
			r = ARCHIVE_WARN;
		}
		__archive_read_consume(a, cpio->entry_bytes_remaining);
		cpio->entry_bytes_remaining = 0;
	}
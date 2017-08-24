{
		/* Convert symlink name too. */
		pathname = archive_entry_symlink(file->entry);
		archive_strcpy(&(file->symlink),  pathname);
#if defined(_WIN32) || defined(__CYGWIN__)
		/*
		 * Convert a path-separator from '\' to  '/'
		 */
		if (archive_strlen(&(file->symlink)) > 0 &&
		    cleanup_backslash_1(file->symlink.s) != 0) {
			const wchar_t *wp =
			    archive_entry_symlink_w(file->entry);
			struct archive_wstring ws;

			if (wp != NULL) {
				int r;
				archive_string_init(&ws);
				archive_wstrcpy(&ws, wp);
				cleanup_backslash_2(ws.s);
				archive_string_empty(&(file->symlink));
				r = archive_string_append_from_wcs(
				    &(file->symlink),
				    ws.s, ws.length);
				archive_wstring_free(&ws);
				if (r < 0 && errno == ENOMEM) {
					archive_set_error(&a->archive, ENOMEM,
					    "Can't allocate memory");
					return (ARCHIVE_FATAL);
				}
			}
		}
#endif
	}
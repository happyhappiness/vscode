(hardlink == NULL) {
		switch (archive_entry_filetype(entry_original)) {
		case AE_IFBLK:
		case AE_IFCHR:
		case AE_IFIFO:
		case AE_IFLNK:
		case AE_IFREG:
			break;
		case AE_IFDIR:
		{
			/*
			 * Ensure a trailing '/'.  Modify the original
			 * entry so the client sees the change.
			 */
#if defined(_WIN32) && !defined(__CYGWIN__)
			const wchar_t *wp;

			wp = archive_entry_pathname_w(entry_original);
			if (wp != NULL && wp[wcslen(wp) -1] != L'/') {
				struct archive_wstring ws;

				archive_string_init(&ws);
				path_length = wcslen(wp);
				if (archive_wstring_ensure(&ws,
				    path_length + 2) == NULL) {
					archive_set_error(&a->archive, ENOMEM,
					    "Can't allocate pax data");
					archive_wstring_free(&ws);
					return(ARCHIVE_FATAL);
				}
				/* Should we keep '\' ? */
				if (wp[path_length -1] == L'\\')
					path_length--;
				archive_wstrncpy(&ws, wp, path_length);
				archive_wstrappend_wchar(&ws, L'/');
				archive_entry_copy_pathname_w(
				    entry_original, ws.s);
				archive_wstring_free(&ws);
				p = NULL;
			} else
#endif
				p = archive_entry_pathname(entry_original);
			/*
			 * On Windows, this is a backup operation just in
			 * case getting WCS failed. On POSIX, this is a
			 * normal operation.
			 */
			if (p != NULL && p[strlen(p) - 1] != '/') {
				struct archive_string as;

				archive_string_init(&as);
				path_length = strlen(p);
				if (archive_string_ensure(&as,
				    path_length + 2) == NULL) {
					archive_set_error(&a->archive, ENOMEM,
					    "Can't allocate pax data");
					archive_string_free(&as);
					return(ARCHIVE_FATAL);
				}
#if defined(_WIN32) && !defined(__CYGWIN__)
				/* NOTE: This might break the pathname
				 * if the current code page is CP932 and
				 * the pathname includes a character '\'
				 * as a part of its multibyte pathname. */
				if (p[strlen(p) -1] == '\\')
					path_length--;
				else
#endif
				archive_strncpy(&as, p, path_length);
				archive_strappend_char(&as, '/');
				archive_entry_copy_pathname(
				    entry_original, as.s);
				archive_string_free(&as);
			}
			break;
		}
		case AE_IFSOCK:
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "tar format cannot archive socket");
			return (ARCHIVE_FAILED);
		default:
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "tar format cannot archive this (type=0%lo)",
			    (unsigned long)
			    archive_entry_filetype(entry_original));
			return (ARCHIVE_FAILED);
		}
	}
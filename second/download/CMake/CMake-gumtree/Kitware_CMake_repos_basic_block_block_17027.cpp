{
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
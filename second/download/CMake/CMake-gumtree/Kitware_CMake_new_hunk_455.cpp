		}
	}

	/* Make sure directories end in '/' */
	if ((zip_entry->mode & AE_IFMT) == AE_IFDIR) {
		wp = archive_entry_pathname_w(entry);
		if (wp != NULL) {
			len = wcslen(wp);
			if (len > 0 && wp[len - 1] != L'/') {
				struct archive_wstring s;
				archive_string_init(&s);
				archive_wstrcat(&s, wp);
				archive_wstrappend_wchar(&s, L'/');
				archive_entry_copy_pathname_w(entry, s.s);
			}
		} else {
			cp = archive_entry_pathname(entry);
			len = (cp != NULL)?strlen(cp):0;
			if (len > 0 && cp[len - 1] != '/') {
				struct archive_string s;
				archive_string_init(&s);
				archive_strcat(&s, cp);
				archive_strappend_char(&s, '/');
				archive_entry_set_pathname(entry, s.s);
			}
		}
	}

	if (zip_entry->flags & LA_FROM_CENTRAL_DIRECTORY) {
		/* If this came from the central dir, it's size info
		 * is definitive, so ignore the length-at-end flag. */

(wp != NULL) {
			len = wcslen(wp);
			if (len > 0 && wp[len - 1] != L'/') {
				struct archive_wstring s;
				archive_string_init(&s);
				archive_wstrcat(&s, wp);
				archive_wstrappend_wchar(&s, L'/');
				archive_entry_copy_pathname_w(entry, s.s);
				archive_wstring_free(&s);
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
				archive_string_free(&s);
			}
		}
(len > 0 && wp[len - 1] != L'/') {
				struct archive_wstring s;
				archive_string_init(&s);
				archive_wstrcat(&s, wp);
				archive_wstrappend_wchar(&s, L'/');
				archive_entry_copy_pathname_w(entry, s.s);
				archive_wstring_free(&s);
			}
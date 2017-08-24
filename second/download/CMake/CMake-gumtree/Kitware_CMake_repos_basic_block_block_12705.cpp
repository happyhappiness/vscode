((wp = archive_entry_pathname_w(entry)) != NULL) {
			l = wcslen(wp);
			if (l > 0 && wp[l - 1] == L'/') {
				archive_entry_set_filetype(entry, AE_IFDIR);
			}
		} else if ((p = archive_entry_pathname(entry)) != NULL) {
			l = strlen(p);
			if (l > 0 && p[l - 1] == '/') {
				archive_entry_set_filetype(entry, AE_IFDIR);
			}
		}
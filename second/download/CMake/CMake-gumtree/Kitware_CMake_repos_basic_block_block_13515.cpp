(wp != NULL) {
			len = wcslen(wp);
			has_slash = len > 0 && wp[len - 1] == L'/';
		} else {
			cp = archive_entry_pathname(entry);
			len = (cp != NULL)?strlen(cp):0;
			has_slash = len > 0 && cp[len - 1] == '/';
		}
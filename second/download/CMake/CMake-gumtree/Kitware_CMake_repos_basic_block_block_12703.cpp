{
			l = strlen(p);
			if (l > 0 && p[l - 1] == '/') {
				archive_entry_set_filetype(entry, AE_IFDIR);
			}
		}
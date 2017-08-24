(sconv == NULL && !pax->opt_binary) {
		if (hardlink != NULL) {
			r = get_entry_hardlink(a, entry_main, &hardlink,
			    &hardlink_length, NULL);
			if (r == ARCHIVE_FATAL)
				return (r);
			linkpath = hardlink;
			linkpath_length = hardlink_length;
		}
		r = get_entry_pathname(a, entry_main, &path,
		    &path_length, NULL);
		if (r == ARCHIVE_FATAL)
			return (r);
		r = get_entry_uname(a, entry_main, &uname, &uname_length, NULL);
		if (r == ARCHIVE_FATAL)
			return (r);
		r = get_entry_gname(a, entry_main, &gname, &gname_length, NULL);
		if (r == ARCHIVE_FATAL)
			return (r);
	}
{
	int r;

	if (a->inclusion_uids.count) {
		if (!match_owner_id(&(a->inclusion_uids),
		    archive_entry_uid(entry)))
			return (1);
	}

	if (a->inclusion_gids.count) {
		if (!match_owner_id(&(a->inclusion_gids),
		    archive_entry_gid(entry)))
			return (1);
	}

	if (a->inclusion_unames.count) {
#if defined(_WIN32) && !defined(__CYGWIN__)
		r = match_owner_name_wcs(a, &(a->inclusion_unames),
			archive_entry_uname_w(entry));
#else
		r = match_owner_name_mbs(a, &(a->inclusion_unames),
			archive_entry_uname(entry));
#endif
		if (!r)
			return (1);
		else if (r < 0)
			return (r);
	}

	if (a->inclusion_gnames.count) {
#if defined(_WIN32) && !defined(__CYGWIN__)
		r = match_owner_name_wcs(a, &(a->inclusion_gnames),
			archive_entry_gname_w(entry));
#else
		r = match_owner_name_mbs(a, &(a->inclusion_gnames),
			archive_entry_gname(entry));
#endif
		if (!r)
			return (1);
		else if (r < 0)
			return (r);
	}
	return (0);
}
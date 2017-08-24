(a->older_mtime_filter) {
		sec = archive_entry_mtime(entry);
		if (sec > a->older_mtime_sec)
			return (1); /* Too new, skip it. */
		nsec = archive_entry_mtime_nsec(entry);
		if (sec == a->older_mtime_sec) {
			if (nsec > a->older_mtime_nsec)
				return (1); /* Too new, skip it. */
			if (nsec == a->older_mtime_nsec &&
			    (a->older_mtime_filter & ARCHIVE_MATCH_EQUAL)
			       == 0)
				return (1); /* Equal, skip it. */
		}
	}
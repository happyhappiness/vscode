(sec == a->older_ctime_sec) {
			if (archive_entry_ctime_is_set(entry))
				nsec = archive_entry_ctime_nsec(entry);
			else
				nsec = archive_entry_mtime_nsec(entry);
			if (nsec > a->older_ctime_nsec)
				return (1); /* Too new, skip it. */
			if (nsec == a->older_ctime_nsec &&
			    (a->older_ctime_filter & ARCHIVE_MATCH_EQUAL)
			      == 0)
				return (1); /* Equal, skip it. */
		}
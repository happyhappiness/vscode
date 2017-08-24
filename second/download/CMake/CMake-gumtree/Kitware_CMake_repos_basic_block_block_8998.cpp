(nsec == a->newer_mtime_nsec &&
			    (a->newer_mtime_filter & ARCHIVE_MATCH_EQUAL)
			       == 0)
				return (1);
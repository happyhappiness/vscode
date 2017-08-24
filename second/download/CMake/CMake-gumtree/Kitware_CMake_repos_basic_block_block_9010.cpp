(nsec == a->newer_ctime_nsec &&
			    (a->newer_ctime_filter & ARCHIVE_MATCH_EQUAL)
			      == 0)
				return (1);
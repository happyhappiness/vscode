((flag & (ARCHIVE_MATCH_NEWER | ARCHIVE_MATCH_OLDER
	    | ARCHIVE_MATCH_EQUAL)) == 0) {
		archive_set_error(_a, EINVAL, "No comparison flag");
		return (ARCHIVE_FAILED);
	}
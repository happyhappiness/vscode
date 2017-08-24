((flag & (ARCHIVE_MATCH_MTIME | ARCHIVE_MATCH_CTIME)) == 0) {
		archive_set_error(_a, EINVAL, "No time flag");
		return (ARCHIVE_FAILED);
	}
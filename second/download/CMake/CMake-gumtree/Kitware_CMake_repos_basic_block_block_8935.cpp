(flag &
	   ((~(ARCHIVE_MATCH_NEWER | ARCHIVE_MATCH_OLDER
			| ARCHIVE_MATCH_EQUAL)) & 0x00ff)) {
		archive_set_error(_a, EINVAL, "Invalid comparison flag");
		return (ARCHIVE_FAILED);
	}
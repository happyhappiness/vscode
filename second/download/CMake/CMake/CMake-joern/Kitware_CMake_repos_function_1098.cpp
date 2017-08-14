static int
validate_time_flag(struct archive *_a, int flag, const char *_fn)
{
	archive_check_magic(_a, ARCHIVE_MATCH_MAGIC,
	    ARCHIVE_STATE_NEW, _fn);

	/* Check a type of time. */
	if (flag &
	   ((~(ARCHIVE_MATCH_MTIME | ARCHIVE_MATCH_CTIME)) & 0xff00)) {
		archive_set_error(_a, EINVAL, "Invalid time flag");
		return (ARCHIVE_FAILED);
	}
	if ((flag & (ARCHIVE_MATCH_MTIME | ARCHIVE_MATCH_CTIME)) == 0) {
		archive_set_error(_a, EINVAL, "No time flag");
		return (ARCHIVE_FAILED);
	}

	/* Check a type of comparison. */
	if (flag &
	   ((~(ARCHIVE_MATCH_NEWER | ARCHIVE_MATCH_OLDER
			| ARCHIVE_MATCH_EQUAL)) & 0x00ff)) {
		archive_set_error(_a, EINVAL, "Invalid comparison flag");
		return (ARCHIVE_FAILED);
	}
	if ((flag & (ARCHIVE_MATCH_NEWER | ARCHIVE_MATCH_OLDER
	    | ARCHIVE_MATCH_EQUAL)) == 0) {
		archive_set_error(_a, EINVAL, "No comparison flag");
		return (ARCHIVE_FAILED);
	}

	return (ARCHIVE_OK);
}
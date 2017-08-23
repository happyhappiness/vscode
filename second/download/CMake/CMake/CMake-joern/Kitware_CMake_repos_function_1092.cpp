int
archive_match_path_excluded(struct archive *_a,
    struct archive_entry *entry)
{
	struct archive_match *a;

	archive_check_magic(_a, ARCHIVE_MATCH_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_match_path_excluded");

	a = (struct archive_match *)_a;
	if (entry == NULL) {
		archive_set_error(&(a->archive), EINVAL, "entry is NULL");
		return (ARCHIVE_FAILED);
	}

	/* If we don't have exclusion/inclusion pattern set at all,
	 * the entry is always not excluded. */
	if ((a->setflag & PATTERN_IS_SET) == 0)
		return (0);
#if defined(_WIN32) && !defined(__CYGWIN__)
	return (path_excluded(a, 0, archive_entry_pathname_w(entry)));
#else
	return (path_excluded(a, 1, archive_entry_pathname(entry)));
#endif
}
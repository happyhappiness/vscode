int
archive_match_excluded(struct archive *_a, struct archive_entry *entry)
{
	struct archive_match *a;
	int r;

	archive_check_magic(_a, ARCHIVE_MATCH_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_match_excluded_ae");

	a = (struct archive_match *)_a;
	if (entry == NULL) {
		archive_set_error(&(a->archive), EINVAL, "entry is NULL");
		return (ARCHIVE_FAILED);
	}

	r = 0;
	if (a->setflag & PATTERN_IS_SET) {
#if defined(_WIN32) && !defined(__CYGWIN__)
		r = path_excluded(a, 0, archive_entry_pathname_w(entry));
#else
		r = path_excluded(a, 1, archive_entry_pathname(entry));
#endif
		if (r != 0)
			return (r);
	}

	if (a->setflag & TIME_IS_SET) {
		r = time_excluded(a, entry);
		if (r != 0)
			return (r);
	}

	if (a->setflag & ID_IS_SET)
		r = owner_excluded(a, entry);
	return (r);
}
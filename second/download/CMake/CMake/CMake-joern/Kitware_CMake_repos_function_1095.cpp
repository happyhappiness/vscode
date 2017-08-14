int
archive_match_time_excluded(struct archive *_a,
    struct archive_entry *entry)
{
	struct archive_match *a;

	archive_check_magic(_a, ARCHIVE_MATCH_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_match_time_excluded_ae");

	a = (struct archive_match *)_a;
	if (entry == NULL) {
		archive_set_error(&(a->archive), EINVAL, "entry is NULL");
		return (ARCHIVE_FAILED);
	}

	/* If we don't have inclusion time set at all, the entry is always
	 * not excluded. */
	if ((a->setflag & TIME_IS_SET) == 0)
		return (0);
	return (time_excluded(a, entry));
}
int
archive_match_exclude_entry(struct archive *_a, int flag,
    struct archive_entry *entry)
{
	struct archive_match *a;
	int r;

	archive_check_magic(_a, ARCHIVE_MATCH_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_match_time_include_entry");
	a = (struct archive_match *)_a;

	if (entry == NULL) {
		archive_set_error(&(a->archive), EINVAL, "entry is NULL");
		return (ARCHIVE_FAILED);
	}
	r = validate_time_flag(_a, flag, "archive_match_exclude_entry");
	if (r != ARCHIVE_OK)
		return (r);
	return (add_entry(a, flag, entry));
}
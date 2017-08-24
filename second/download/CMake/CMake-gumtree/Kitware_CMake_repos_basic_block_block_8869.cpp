{
	struct archive_match *a;
	int r;

	archive_check_magic(_a, ARCHIVE_MATCH_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_match_include_pattern_w");
	a = (struct archive_match *)_a;

	if (pattern == NULL || *pattern == L'\0') {
		archive_set_error(&(a->archive), EINVAL, "pattern is empty");
		return (ARCHIVE_FAILED);
	}
	if ((r = add_pattern_wcs(a, &(a->inclusions), pattern)) != ARCHIVE_OK)
		return (r);
	return (ARCHIVE_OK);
}
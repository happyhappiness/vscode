{
	int r;

	r = validate_time_flag(_a, flag, "archive_match_include_date");
	if (r != ARCHIVE_OK)
		return (r);
	return set_timefilter_date((struct archive_match *)_a, flag, datestr);
}
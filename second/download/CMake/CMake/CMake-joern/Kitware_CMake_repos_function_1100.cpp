static int
set_timefilter_date(struct archive_match *a, int timetype, const char *datestr)
{
	time_t t;

	if (datestr == NULL || *datestr == '\0') {
		archive_set_error(&(a->archive), EINVAL, "date is empty");
		return (ARCHIVE_FAILED);
	}
	t = get_date(a->now, datestr);
	if (t == (time_t)-1) {
		archive_set_error(&(a->archive), EINVAL, "invalid date string");
		return (ARCHIVE_FAILED);
	}
	return set_timefilter(a, timetype, t, 0, t, 0);
}
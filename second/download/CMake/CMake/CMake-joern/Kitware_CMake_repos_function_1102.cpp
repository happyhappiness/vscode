static int
set_timefilter_date_w(struct archive_match *a, int timetype,
    const wchar_t *datestr)
{
	struct archive_string as;
	time_t t;

	if (datestr == NULL || *datestr == L'\0') {
		archive_set_error(&(a->archive), EINVAL, "date is empty");
		return (ARCHIVE_FAILED);
	}

	archive_string_init(&as);
	if (archive_string_append_from_wcs(&as, datestr, wcslen(datestr)) < 0) {
		archive_string_free(&as);
		if (errno == ENOMEM)
			return (error_nomem(a));
		archive_set_error(&(a->archive), -1,
		    "Failed to convert WCS to MBS");
		return (ARCHIVE_FAILED);
	}
	t = get_date(a->now, as.s);
	archive_string_free(&as);
	if (t == (time_t)-1) {
		archive_set_error(&(a->archive), EINVAL, "invalid date string");
		return (ARCHIVE_FAILED);
	}
	return set_timefilter(a, timetype, t, 0, t, 0);
}
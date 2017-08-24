{
	struct archive_string as;
	int r;

	if (path == NULL || *path == L'\0') {
		archive_set_error(&(a->archive), EINVAL, "pathname is empty");
		return (ARCHIVE_FAILED);
	}

	/* Convert WCS filename to MBS filename. */
	archive_string_init(&as);
	if (archive_string_append_from_wcs(&as, path, wcslen(path)) < 0) {
		archive_string_free(&as);
		if (errno == ENOMEM)
			return (error_nomem(a));
		archive_set_error(&(a->archive), -1,
		    "Failed to convert WCS to MBS");
		return (ARCHIVE_FAILED);
	}

	r = set_timefilter_pathname_mbs(a, timetype, as.s);
	archive_string_free(&as);

	return (r);
}
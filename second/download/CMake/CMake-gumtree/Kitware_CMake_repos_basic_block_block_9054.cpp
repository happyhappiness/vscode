{
	int r1, r2;

	if (o == NULL && v == NULL)
		return (ARCHIVE_OK);
	if (o == NULL)
		return (ARCHIVE_FAILED);

	r1 = use_format_option(a, m, o, v);
	if (r1 == ARCHIVE_FATAL)
		return (ARCHIVE_FATAL);

	r2 = use_filter_option(a, m, o, v);
	if (r2 == ARCHIVE_FATAL)
		return (ARCHIVE_FATAL);

	if (r2 == ARCHIVE_WARN - 1)
		return r1;
	return r1 > r2 ? r1 : r2;
}
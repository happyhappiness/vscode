{
	struct archive_read *a = (struct archive_read *)_a;
	struct archive_read_filter *filter;
	struct archive_read_filter_bidder *bidder;
	int r, rv = ARCHIVE_WARN, matched_modules = 0;

	for (filter = a->filter; filter != NULL; filter = filter->upstream) {
		bidder = filter->bidder;
		if (bidder == NULL)
			continue;
		if (bidder->options == NULL)
			/* This bidder does not support option */
			continue;
		if (m != NULL) {
			if (strcmp(filter->name, m) != 0)
				continue;
			++matched_modules;
		}

		r = bidder->options(bidder, o, v);

		if (r == ARCHIVE_FATAL)
			return (ARCHIVE_FATAL);

		if (r == ARCHIVE_OK)
			rv = ARCHIVE_OK;
	}
	/* If the filter name didn't match, return a special code for
	 * _archive_set_option[s]. */
	if (m != NULL && matched_modules == 0)
		return ARCHIVE_WARN - 1;
	return (rv);
}
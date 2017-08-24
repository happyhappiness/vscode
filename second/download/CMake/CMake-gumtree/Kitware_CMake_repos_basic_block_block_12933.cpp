{
	int64_t l, limit, last_digit_limit;
	const char *p;
	ssize_t bytes_read;
	int base, digit;

	base = 10;
	limit = INT64_MAX / base;
	last_digit_limit = INT64_MAX % base;

	/*
	 * Skip any lines starting with '#'; GNU tar specs
	 * don't require this, but they should.
	 */
	do {
		bytes_read = readline(a, tar, &p,
			(ssize_t)tar_min(*remaining, 100), unconsumed);
		if (bytes_read <= 0)
			return (ARCHIVE_FATAL);
		*remaining -= bytes_read;
	} while (p[0] == '#');

	l = 0;
	while (bytes_read > 0) {
		if (*p == '\n')
			return (l);
		if (*p < '0' || *p >= '0' + base)
			return (ARCHIVE_WARN);
		digit = *p - '0';
		if (l > limit || (l == limit && digit > last_digit_limit))
			l = INT64_MAX; /* Truncate on overflow. */
		else
			l = (l * base) + digit;
		p++;
		bytes_read--;
	}
	/* TODO: Error message. */
	return (ARCHIVE_WARN);
}
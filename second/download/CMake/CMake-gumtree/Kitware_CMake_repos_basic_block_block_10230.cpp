{
	const unsigned char *p;
	ssize_t avail, len;
	int i;

	(void)self; /* UNUSED */
	/* Start by looking at the first six bytes of the header, which
	 * is all fixed layout. */
	len = 6;
	p = __archive_read_filter_ahead(filter, len, &avail);
	if (p == NULL || avail == 0)
		return (0);

	if (memcmp(p, LRZIP_HEADER_MAGIC, LRZIP_HEADER_MAGIC_LEN))
		return (0);

	/* current major version is always 0, verify this */
	if (p[LRZIP_HEADER_MAGIC_LEN])
		return 0;
	/* support only v0.6+ lrzip for sanity */
	i = p[LRZIP_HEADER_MAGIC_LEN + 1];
	if ((i < 6) || (i > 10))
		return 0;

	return (int)len;
}
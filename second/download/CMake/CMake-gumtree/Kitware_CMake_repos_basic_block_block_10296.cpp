{
	const unsigned char *p;
	ssize_t avail;

	(void)self; /* UNUSED */

	p = __archive_read_filter_ahead(filter, LZOP_HEADER_MAGIC_LEN, &avail);
	if (p == NULL || avail == 0)
		return (0);

	if (memcmp(p, LZOP_HEADER_MAGIC, LZOP_HEADER_MAGIC_LEN))
		return (0);

	return (LZOP_HEADER_MAGIC_LEN * 8);
}
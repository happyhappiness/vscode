{
	const unsigned char *buffer;
	ssize_t avail;

	(void)self; /* UNUSED */

	buffer = __archive_read_filter_ahead(filter, 6, &avail);
	if (buffer == NULL)
		return (0);

	/*
	 * Verify Header Magic Bytes : FD 37 7A 58 5A 00
	 */
	if (memcmp(buffer, "\xFD\x37\x7A\x58\x5A\x00", 6) != 0)
		return (0);

	return (48);
}
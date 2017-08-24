{
	const unsigned char *buffer;
	ssize_t avail;
	int bits_checked;

	(void)self; /* UNUSED */

	/* Shortest valid compress file is 3 bytes. */
	buffer = __archive_read_filter_ahead(filter, 3, &avail);

	if (buffer == NULL)
		return (0);

	bits_checked = 0;
	/* First two bytes are the magic value */
	if (buffer[0] != 0x1F || buffer[1] != 0x9D)
		return (0);
	/* Third byte holds compression parameters. */
	if (buffer[2] & 0x20) /* Reserved bit, must be zero. */
		return (0);
	if (buffer[2] & 0x40) /* Reserved bit, must be zero. */
		return (0);
	bits_checked += 18;

	return (bits_checked);
}
{
	const unsigned char *buffer;
	ssize_t avail;
	int bits_checked;
	uint32_t number;

	(void)self; /* UNUSED */

	/* Minimal lz4 archive is 11 bytes. */
	buffer = __archive_read_filter_ahead(filter, 11, &avail);
	if (buffer == NULL)
		return (0);

	/* First four bytes must be LZ4 magic numbers. */
	bits_checked = 0;
	if ((number = archive_le32dec(buffer)) == LZ4_MAGICNUMBER) {
		unsigned char flag, BD;

		bits_checked += 32;
		/* Next follows a stream descriptor. */
		/* Descriptor Flags. */
		flag = buffer[4];
		/* A version number must be "01". */
		if (((flag & 0xc0) >> 6) != 1)
			return (0);
		/* A reserved bit must be "0". */
		if (flag & 2)
			return (0);
		bits_checked += 8;
		BD = buffer[5];
		/* A block maximum size should be more than 3. */
		if (((BD & 0x70) >> 4) < 4)
			return (0);
		/* Reserved bits must be "0". */
		if (BD & ~0x70)
			return (0);
		bits_checked += 8;
	} else if (number == LZ4_LEGACY) {
		bits_checked += 32;
	}
	
	return (bits_checked);
}
{
	const unsigned char *p;
	ssize_t avail, len;
	int bits = 0;
	int header_flags;

	/* Start by looking at the first ten bytes of the header, which
	 * is all fixed layout. */
	len = 10;
	p = __archive_read_filter_ahead(filter, len, &avail);
	if (p == NULL || avail == 0)
		return (0);
	/* We only support deflation- third byte must be 0x08. */
	if (memcmp(p, "\x1F\x8B\x08", 3) != 0)
		return (0);
	bits += 24;
	if ((p[3] & 0xE0)!= 0)	/* No reserved flags set. */
		return (0);
	bits += 3;
	header_flags = p[3];
	/* Bytes 4-7 are mod time. */
	/* Byte 8 is deflate flags. */
	/* XXXX TODO: return deflate flags back to consume_header for use
	   in initializing the decompressor. */
	/* Byte 9 is OS. */

	/* Optional extra data:  2 byte length plus variable body. */
	if (header_flags & 4) {
		p = __archive_read_filter_ahead(filter, len + 2, &avail);
		if (p == NULL)
			return (0);
		len += ((int)p[len + 1] << 8) | (int)p[len];
		len += 2;
	}

	/* Null-terminated optional filename. */
	if (header_flags & 8) {
		do {
			++len;
			if (avail < len)
				p = __archive_read_filter_ahead(filter,
				    len, &avail);
			if (p == NULL)
				return (0);
		} while (p[len - 1] != 0);
	}

	/* Null-terminated optional comment. */
	if (header_flags & 16) {
		do {
			++len;
			if (avail < len)
				p = __archive_read_filter_ahead(filter,
				    len, &avail);
			if (p == NULL)
				return (0);
		} while (p[len - 1] != 0);
	}

	/* Optional header CRC */
	if ((header_flags & 2)) {
		p = __archive_read_filter_ahead(filter, len + 2, &avail);
		if (p == NULL)
			return (0);
#if 0
	int hcrc = ((int)p[len + 1] << 8) | (int)p[len];
	int crc = /* XXX TODO: Compute header CRC. */;
	if (crc != hcrc)
		return (0);
	bits += 16;
#endif
		len += 2;
	}

	if (pbits != NULL)
		*pbits = bits;
	return (len);
}
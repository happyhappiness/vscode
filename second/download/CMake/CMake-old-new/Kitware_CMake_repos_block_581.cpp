{
	struct read_lzop *state = (struct read_lzop *)self->data;
	const unsigned char *p, *_p;
	unsigned checksum, flags, len, method, version;

	/*
	 * Check LZOP magic code.
	 */
	p = __archive_read_filter_ahead(self->upstream,
		LZOP_HEADER_MAGIC_LEN, NULL);
	if (p == NULL)
		return (ARCHIVE_EOF);

	if (memcmp(p, LZOP_HEADER_MAGIC, LZOP_HEADER_MAGIC_LEN))
		return (ARCHIVE_EOF);
	__archive_read_filter_consume(self->upstream,
	    LZOP_HEADER_MAGIC_LEN);

	p = __archive_read_filter_ahead(self->upstream, 29, NULL);
	if (p == NULL)
		goto truncated;
	_p = p;
	version = archive_be16dec(p);
	p += 4;/* version(2 bytes) + library version(2 bytes) */

	if (version >= 0x940) {
		unsigned reqversion = archive_be16dec(p); p += 2;
		if (reqversion < 0x900) {
			archive_set_error(&self->archive->archive,
			    ARCHIVE_ERRNO_MISC, "Invalid required version");
			return (ARCHIVE_FAILED);
		}
	}

	method = *p++;
	if (method < 1 || method > 3) {
		archive_set_error(&self->archive->archive, ARCHIVE_ERRNO_MISC,
		    "Unsupported method");
		return (ARCHIVE_FAILED);
	}

	if (version >= 0x940) {
		unsigned level = *p++;
#if 0
		unsigned default_level[] = {0, 3, 1, 9};
#endif
		if (level == 0)
			/* Method is 1..3 here due to check above. */
#if 0	/* Avoid an error Clang Static Analyzer claims
	  "Value stored to 'level' is never read". */
			level = default_level[method];
#else
			;/* NOP */
#endif
		else if (level > 9) {
			archive_set_error(&self->archive->archive,
			    ARCHIVE_ERRNO_MISC, "Invalid level");
			return (ARCHIVE_FAILED);
		}
	}

	flags = archive_be32dec(p); p += 4;

	if (flags & FILTER)
		p += 4; /* Skip filter */
	p += 4; /* Skip mode */
	if (version >= 0x940)
		p += 8; /* Skip mtime */
	else
		p += 4; /* Skip mtime */
	len = *p++; /* Read filename length */
	len += p - _p;
	/* Make sure we have all bytes we need to calculate checksum. */
	p = __archive_read_filter_ahead(self->upstream, len + 4, NULL);
	if (p == NULL)
		goto truncated;
	if (flags & CRC32_HEADER)
		checksum = crc32(crc32(0, NULL, 0), p, len);
	else
		checksum = adler32(adler32(0, NULL, 0), p, len);
	if (archive_be32dec(p + len) != checksum)
		goto corrupted;
	__archive_read_filter_consume(self->upstream, len + 4);
	if (flags & EXTRA_FIELD) {
		/* Skip extra field */
		p = __archive_read_filter_ahead(self->upstream, 4, NULL);
		if (p == NULL)
			goto truncated;
		len = archive_be32dec(p);
		__archive_read_filter_consume(self->upstream, len + 4 + 4);
	}
	state->flags = flags;
	state->in_stream = 1;
	return (ARCHIVE_OK);
truncated:
	archive_set_error(&self->archive->archive,
	    ARCHIVE_ERRNO_FILE_FORMAT, "Truncated lzop data");
	return (ARCHIVE_FAILED);
corrupted:
	archive_set_error(&self->archive->archive,
	    ARCHIVE_ERRNO_FILE_FORMAT, "Corrupted lzop header");
	return (ARCHIVE_FAILED);
}
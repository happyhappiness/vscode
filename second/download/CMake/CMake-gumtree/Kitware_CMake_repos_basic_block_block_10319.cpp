{
	struct read_lzop *state = (struct read_lzop *)self->data;
	const unsigned char *p;
	unsigned flags = state->flags;

	p = __archive_read_filter_ahead(self->upstream, 4, NULL);
	if (p == NULL)
		goto truncated;
	state->uncompressed_size = archive_be32dec(p);
	__archive_read_filter_consume(self->upstream, 4);
	if (state->uncompressed_size == 0)
		return (ARCHIVE_EOF);
	if (state->uncompressed_size > MAX_BLOCK_SIZE)
		goto corrupted;

	p = __archive_read_filter_ahead(self->upstream, 4, NULL);
	if (p == NULL)
		goto truncated;
	state->compressed_size = archive_be32dec(p);
	__archive_read_filter_consume(self->upstream, 4);
	if (state->compressed_size > state->uncompressed_size)
		goto corrupted;

	if (flags & (CRC32_UNCOMPRESSED | ADLER32_UNCOMPRESSED)) {
		p = __archive_read_filter_ahead(self->upstream, 4, NULL);
		if (p == NULL)
			goto truncated;
		state->compressed_cksum = state->uncompressed_cksum =
		    archive_be32dec(p);
		__archive_read_filter_consume(self->upstream, 4);
	}
	if ((flags & (CRC32_COMPRESSED | ADLER32_COMPRESSED)) &&
	    state->compressed_size < state->uncompressed_size) {
		p = __archive_read_filter_ahead(self->upstream, 4, NULL);
		if (p == NULL)
			goto truncated;
		state->compressed_cksum = archive_be32dec(p);
		__archive_read_filter_consume(self->upstream, 4);
	}
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
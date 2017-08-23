static int
consume_header(struct archive_read_filter *self)
{
	struct private_data *state;
	ssize_t avail;
	size_t len;
	int ret;

	state = (struct private_data *)self->data;

	/* If this is a real header, consume it. */
	len = peek_at_header(self->upstream, NULL);
	if (len == 0)
		return (ARCHIVE_EOF);
	__archive_read_filter_consume(self->upstream, len);

	/* Initialize CRC accumulator. */
	state->crc = crc32(0L, NULL, 0);

	/* Initialize compression library. */
	state->stream.next_in = (unsigned char *)(uintptr_t)
	    __archive_read_filter_ahead(self->upstream, 1, &avail);
	state->stream.avail_in = (uInt)avail;
	ret = inflateInit2(&(state->stream),
	    -15 /* Don't check for zlib header */);

	/* Decipher the error code. */
	switch (ret) {
	case Z_OK:
		state->in_stream = 1;
		return (ARCHIVE_OK);
	case Z_STREAM_ERROR:
		archive_set_error(&self->archive->archive,
		    ARCHIVE_ERRNO_MISC,
		    "Internal error initializing compression library: "
		    "invalid setup parameter");
		break;
	case Z_MEM_ERROR:
		archive_set_error(&self->archive->archive, ENOMEM,
		    "Internal error initializing compression library: "
		    "out of memory");
		break;
	case Z_VERSION_ERROR:
		archive_set_error(&self->archive->archive,
		    ARCHIVE_ERRNO_MISC,
		    "Internal error initializing compression library: "
		    "invalid library version");
		break;
	default:
		archive_set_error(&self->archive->archive,
		    ARCHIVE_ERRNO_MISC,
		    "Internal error initializing compression library: "
		    " Zlib error %d", ret);
		break;
	}
	return (ARCHIVE_FATAL);
}
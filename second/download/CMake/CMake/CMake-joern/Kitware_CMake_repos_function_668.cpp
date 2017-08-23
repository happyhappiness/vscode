static int
consume_trailer(struct archive_read_filter *self)
{
	struct private_data *state;
	const unsigned char *p;
	ssize_t avail;

	state = (struct private_data *)self->data;

	state->in_stream = 0;
	switch (inflateEnd(&(state->stream))) {
	case Z_OK:
		break;
	default:
		archive_set_error(&self->archive->archive,
		    ARCHIVE_ERRNO_MISC,
		    "Failed to clean up gzip decompressor");
		return (ARCHIVE_FATAL);
	}

	/* GZip trailer is a fixed 8 byte structure. */
	p = __archive_read_filter_ahead(self->upstream, 8, &avail);
	if (p == NULL || avail == 0)
		return (ARCHIVE_FATAL);

	/* XXX TODO: Verify the length and CRC. */

	/* We've verified the trailer, so consume it now. */
	__archive_read_filter_consume(self->upstream, 8);

	return (ARCHIVE_OK);
}
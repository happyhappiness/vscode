static int
gzip_filter_close(struct archive_read_filter *self)
{
	struct private_data *state;
	int ret;

	state = (struct private_data *)self->data;
	ret = ARCHIVE_OK;

	if (state->in_stream) {
		switch (inflateEnd(&(state->stream))) {
		case Z_OK:
			break;
		default:
			archive_set_error(&(self->archive->archive),
			    ARCHIVE_ERRNO_MISC,
			    "Failed to clean up gzip compressor");
			ret = ARCHIVE_FATAL;
		}
	}

	free(state->out_block);
	free(state);
	return (ret);
}
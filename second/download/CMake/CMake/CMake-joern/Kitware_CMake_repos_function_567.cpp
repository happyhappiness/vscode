static int
bzip2_filter_close(struct archive_read_filter *self)
{
	struct private_data *state;
	int ret = ARCHIVE_OK;

	state = (struct private_data *)self->data;

	if (state->valid) {
		switch (BZ2_bzDecompressEnd(&state->stream)) {
		case BZ_OK:
			break;
		default:
			archive_set_error(&self->archive->archive,
					  ARCHIVE_ERRNO_MISC,
					  "Failed to clean up decompressor");
			ret = ARCHIVE_FATAL;
		}
		state->valid = 0;
	}

	free(state->out_block);
	free(state);
	return (ret);
}
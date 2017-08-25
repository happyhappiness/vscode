static int
lzma_filter_close(struct archive_read_filter *self)
{
	struct private_data *state;
	int ret;

	state = (struct private_data *)self->data;
	ret = ARCHIVE_OK;
	switch (lzmadec_end(&(state->stream))) {
	case LZMADEC_OK:
		break;
	default:
		archive_set_error(&(self->archive->archive),
		    ARCHIVE_ERRNO_MISC,
		    "Failed to clean up %s compressor",
		    self->archive->archive.compression_name);
		ret = ARCHIVE_FATAL;
	}

	free(state->out_block);
	free(state);
	return (ret);
}
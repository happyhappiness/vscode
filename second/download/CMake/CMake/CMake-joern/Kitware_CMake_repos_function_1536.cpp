static int
lz4_allocate_out_block_for_legacy(struct archive_read_filter *self)
{
	struct private_data *state = (struct private_data *)self->data;
	size_t out_block_size = LEGACY_BLOCK_SIZE;
	void *out_block;

	if (state->out_block_size < out_block_size) {
		free(state->out_block);
		out_block = (unsigned char *)malloc(out_block_size);
		state->out_block_size = out_block_size;
		if (out_block == NULL) {
			archive_set_error(&self->archive->archive, ENOMEM,
			    "Can't allocate data for lz4 decompression");
			return (ARCHIVE_FATAL);
		}
		state->out_block = out_block;
	}
	return (ARCHIVE_OK);
}
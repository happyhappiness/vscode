static int
archive_compressor_compress_open(struct archive_write_filter *f)
{
	int ret;
	struct private_data *state;
	size_t bs = 65536, bpb;

	f->code = ARCHIVE_FILTER_COMPRESS;
	f->name = "compress";

	ret = __archive_write_open_filter(f->next_filter);
	if (ret != ARCHIVE_OK)
		return (ret);

	state = (struct private_data *)calloc(1, sizeof(*state));
	if (state == NULL) {
		archive_set_error(f->archive, ENOMEM,
		    "Can't allocate data for compression");
		return (ARCHIVE_FATAL);
	}

	if (f->archive->magic == ARCHIVE_WRITE_MAGIC) {
		/* Buffer size should be a multiple number of the of bytes
		 * per block for performance. */
		bpb = archive_write_get_bytes_per_block(f->archive);
		if (bpb > bs)
			bs = bpb;
		else if (bpb != 0)
			bs -= bs % bpb;
	}
	state->compressed_buffer_size = bs;
	state->compressed = malloc(state->compressed_buffer_size);

	if (state->compressed == NULL) {
		archive_set_error(f->archive, ENOMEM,
		    "Can't allocate data for compression buffer");
		free(state);
		return (ARCHIVE_FATAL);
	}

	f->write = archive_compressor_compress_write;
	f->close = archive_compressor_compress_close;
	f->free = archive_compressor_compress_free;

	state->max_maxcode = 0x10000;	/* Should NEVER generate this code. */
	state->in_count = 0;		/* Length of input. */
	state->bit_buf = 0;
	state->bit_offset = 0;
	state->out_count = 3;		/* Includes 3-byte header mojo. */
	state->compress_ratio = 0;
	state->checkpoint = CHECK_GAP;
	state->code_len = 9;
	state->cur_maxcode = MAXCODE(state->code_len);
	state->first_free = FIRST;

	memset(state->hashtab, 0xff, sizeof(state->hashtab));

	/* Prime output buffer with a gzip header. */
	state->compressed[0] = 0x1f; /* Compress */
	state->compressed[1] = 0x9d;
	state->compressed[2] = 0x90; /* Block mode, 16bit max */
	state->compressed_offset = 3;

	f->data = state;
	return (0);
}
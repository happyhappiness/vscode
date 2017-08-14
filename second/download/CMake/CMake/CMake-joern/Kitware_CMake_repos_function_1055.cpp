static int
archive_filter_lz4_open(struct archive_write_filter *f)
{
	struct private_data *data = (struct private_data *)f->data;
	int ret;
	size_t required_size;
	static size_t bkmap[] = { 64 * 1024, 256 * 1024, 1 * 1024 * 1024,
			   4 * 1024 * 1024 };
	size_t pre_block_size;

	ret = __archive_write_open_filter(f->next_filter);
	if (ret != 0)
		return (ret);

	if (data->block_maximum_size < 4)
		data->block_size = bkmap[0];
	else
		data->block_size = bkmap[data->block_maximum_size - 4];

	required_size = 4 + 15 + 4 + data->block_size + 4 + 4;
	if (data->out_buffer_size < required_size) {
		size_t bs = required_size, bpb;
		free(data->out_buffer);
		if (f->archive->magic == ARCHIVE_WRITE_MAGIC) {
			/* Buffer size should be a multiple number of
			 * the of bytes per block for performance. */
			bpb = archive_write_get_bytes_per_block(f->archive);
			if (bpb > bs)
				bs = bpb;
			else if (bpb != 0) {
				bs += bpb;
				bs -= bs % bpb;
			}
		}
		data->out_block_size = bs;
		bs += required_size;
		data->out_buffer = malloc(bs);
		data->out = data->out_buffer;
		data->out_buffer_size = bs;
	}

	pre_block_size = (data->block_independence)? 0: 64 * 1024;
	if (data->in_buffer_size < data->block_size + pre_block_size) {
		free(data->in_buffer_allocated);
		data->in_buffer_size = data->block_size;
		data->in_buffer_allocated =
		    malloc(data->in_buffer_size + pre_block_size);
		data->in_buffer = data->in_buffer_allocated + pre_block_size;
		if (!data->block_independence && data->compression_level >= 3)
		    data->in_buffer = data->in_buffer_allocated;
		data->in = data->in_buffer;
		data->in_buffer_size = data->block_size;
	}

	if (data->out_buffer == NULL || data->in_buffer_allocated == NULL) {
		archive_set_error(f->archive, ENOMEM,
		    "Can't allocate data for compression buffer");
		return (ARCHIVE_FATAL);
	}

	f->write = archive_filter_lz4_write;

	return (ARCHIVE_OK);
}
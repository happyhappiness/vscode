{
	struct private_data *data = (struct private_data *)f->data;
	int ret = ARCHIVE_OK;
	const char *p;
	size_t remaining;
	ssize_t size;

	/* If we haven't written a stream descriptor, we have to do it first. */
	if (!data->header_written) {
		ret = lz4_write_stream_descriptor(f);
		if (ret != ARCHIVE_OK)
			return (ret);
		data->header_written = 1;
	}

	/* Update statistics */
	data->total_in += length;

	p = (const char *)buff;
	remaining = length;
	while (remaining) {
		size_t l;
		/* Compress input data to output buffer */
		size = lz4_write_one_block(f, p, remaining);
		if (size < ARCHIVE_OK)
			return (ARCHIVE_FATAL);
		l = data->out - data->out_buffer;
		if (l >= data->out_block_size) {
			ret = __archive_write_filter(f->next_filter,
			    data->out_buffer, data->out_block_size);
			l -= data->out_block_size;
			memcpy(data->out_buffer,
			    data->out_buffer + data->out_block_size, l);
			data->out = data->out_buffer + l;
			if (ret < ARCHIVE_WARN)
				break;
		}
		p += size;
		remaining -= size;
	}

	return (ret);
}
(compressed_size == 0) {
		__archive_read_filter_consume(self->upstream, 4);
		return 0;
	}
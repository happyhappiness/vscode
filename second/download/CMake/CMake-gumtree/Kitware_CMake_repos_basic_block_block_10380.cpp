{
		rpm->total_in += used;
		__archive_read_filter_consume(self->upstream, used);
	}
{
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
{
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
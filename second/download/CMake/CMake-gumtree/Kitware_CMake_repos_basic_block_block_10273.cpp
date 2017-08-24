{
		prefix64k = 0;
		uncompressed_size = LZ4_decompress_safe(read_buf + 4,
		    state->out_block, (int)compressed_size,
		    state->flags.block_maximum_size);
	}
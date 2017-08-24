(i = (size_t)(block->compressed_size); i & 3; ++i) {
		assert(*out_pos < out_size);
		out[(*out_pos)++] = 0x00;
	}
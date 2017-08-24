(in_pos < in_size) {
		if (in[in_pos++] != 0x00) {
			free_properties(block, allocator);

			// Possibly some new field present so use
			// LZMA_OPTIONS_ERROR instead of LZMA_DATA_ERROR.
			return LZMA_OPTIONS_ERROR;
		}
	}
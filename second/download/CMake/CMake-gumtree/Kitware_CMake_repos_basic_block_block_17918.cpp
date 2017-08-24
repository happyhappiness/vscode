(lzma_block_header_encode(block, out + *out_pos) != LZMA_OK) {
		block->filters = filters_orig;
		return LZMA_PROG_ERROR;
	}
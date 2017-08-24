(out_size - *out_pos <= block->header_size)
		return LZMA_BUF_ERROR;
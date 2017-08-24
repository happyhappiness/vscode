(out_size - out_pos <= 2 * LZMA_STREAM_HEADER_SIZE)
		return LZMA_BUF_ERROR;
{
	lzma_coder coder;
	lzma_ret ret;

	// Store the input start position so that we can restore it in case
	// of an error.
	const size_t in_start = *in_pos;

	// Sanity checks
	if (i == NULL || memlimit == NULL
			|| in == NULL || in_pos == NULL || *in_pos > in_size)
		return LZMA_PROG_ERROR;

	// Initialize the decoder.
	return_if_error(index_decoder_reset(&coder, allocator, i, *memlimit));

	// Do the actual decoding.
	ret = index_decode(&coder, allocator, in, in_pos, in_size,
			NULL, NULL, 0, LZMA_RUN);

	if (ret == LZMA_STREAM_END) {
		ret = LZMA_OK;
	} else {
		// Something went wrong, free the Index structure and restore
		// the input position.
		lzma_index_end(coder.index, allocator);
		*in_pos = in_start;

		if (ret == LZMA_OK) {
			// The input is truncated or otherwise corrupt.
			// Use LZMA_DATA_ERROR instead of LZMA_BUF_ERROR
			// like lzma_vli_decode() does in single-call mode.
			ret = LZMA_DATA_ERROR;

		} else if (ret == LZMA_MEMLIMIT_ERROR) {
			// Tell the caller how much memory would have
			// been needed.
			*memlimit = lzma_index_memusage(1, coder.count);
		}
	}

	return ret;
}
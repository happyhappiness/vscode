{
	lzma_coder coder;
	size_t out_start;
	lzma_ret ret;

	// Validate the arguments.
	if (i == NULL || out == NULL || out_pos == NULL || *out_pos > out_size)
		return LZMA_PROG_ERROR;

	// Don't try to encode if there's not enough output space.
	if (out_size - *out_pos < lzma_index_size(i))
		return LZMA_BUF_ERROR;

	// The Index encoder needs just one small data structure so we can
	// allocate it on stack.
	index_encoder_reset(&coder, i);

	// Do the actual encoding. This should never fail, but store
	// the original *out_pos just in case.
	out_start = *out_pos;
	ret = index_encode(&coder, NULL, NULL, NULL, 0,
			out, out_pos, out_size, LZMA_RUN);

	if (ret == LZMA_STREAM_END) {
		ret = LZMA_OK;
	} else {
		// We should never get here, but just in case, restore the
		// output position and set the error accordingly if something
		// goes wrong and debugging isn't enabled.
		assert(0);
		*out_pos = out_start;
		ret = LZMA_PROG_ERROR;
	}

	return ret;
}
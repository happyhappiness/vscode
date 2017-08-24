{
	lzma_stream_flags stream_flags = { 0 };
	lzma_block block = { 0 };
	size_t out_pos;

	// Sanity checks
	if (filters == NULL || (unsigned int)(check) > LZMA_CHECK_ID_MAX
			|| (in == NULL && in_size != 0) || out == NULL
			|| out_pos_ptr == NULL || *out_pos_ptr > out_size)
		return LZMA_PROG_ERROR;

	if (!lzma_check_is_supported(check))
		return LZMA_UNSUPPORTED_CHECK;

	// Note for the paranoids: Index encoder prevents the Stream from
	// getting too big and still being accepted with LZMA_OK, and Block
	// encoder catches if the input is too big. So we don't need to
	// separately check if the buffers are too big.

	// Use a local copy. We update *out_pos_ptr only if everything
	// succeeds.
	out_pos = *out_pos_ptr;

	// Check that there's enough space for both Stream Header and
	// Stream Footer.
	if (out_size - out_pos <= 2 * LZMA_STREAM_HEADER_SIZE)
		return LZMA_BUF_ERROR;

	// Reserve space for Stream Footer so we don't need to check for
	// available space again before encoding Stream Footer.
	out_size -= LZMA_STREAM_HEADER_SIZE;

	// Encode the Stream Header.
	stream_flags.check = check;

	if (lzma_stream_header_encode(&stream_flags, out + out_pos)
			!= LZMA_OK)
		return LZMA_PROG_ERROR;

	out_pos += LZMA_STREAM_HEADER_SIZE;

	// Encode a Block but only if there is at least one byte of input.
	block.check = check;
	block.filters = filters;

	if (in_size > 0)
		return_if_error(lzma_block_buffer_encode(&block, allocator,
				in, in_size, out, &out_pos, out_size));

	// Index
	{
		lzma_ret ret;

		// Create an Index. It will have one Record if there was
		// at least one byte of input to encode. Otherwise the
		// Index will be empty.
		lzma_index *i = lzma_index_init(allocator);
		if (i == NULL)
			return LZMA_MEM_ERROR;

		ret = LZMA_OK;

		if (in_size > 0)
			ret = lzma_index_append(i, allocator,
					lzma_block_unpadded_size(&block),
					block.uncompressed_size);

		// If adding the Record was successful, encode the Index
		// and get its size which will be stored into Stream Footer.
		if (ret == LZMA_OK) {
			ret = lzma_index_buffer_encode(
					i, out, &out_pos, out_size);

			stream_flags.backward_size = lzma_index_size(i);
		}

		lzma_index_end(i, allocator);

		if (ret != LZMA_OK)
			return ret;
	}

	// Stream Footer. We have already reserved space for this.
	if (lzma_stream_footer_encode(&stream_flags, out + out_pos)
			!= LZMA_OK)
		return LZMA_PROG_ERROR;

	out_pos += LZMA_STREAM_HEADER_SIZE;

	// Everything went fine, make the new output position available
	// to the application.
	*out_pos_ptr = out_pos;
	return LZMA_OK;
}
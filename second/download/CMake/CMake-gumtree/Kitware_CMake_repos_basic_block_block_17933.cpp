{
	size_t check_size;
	lzma_ret ret;
	size_t i;

	// Validate the arguments.
	if (block == NULL || (in == NULL && in_size != 0) || out == NULL
			|| out_pos == NULL || *out_pos > out_size)
		return LZMA_PROG_ERROR;

	// The contents of the structure may depend on the version so
	// check the version before validating the contents of *block.
	if (block->version != 0)
		return LZMA_OPTIONS_ERROR;

	if ((unsigned int)(block->check) > LZMA_CHECK_ID_MAX
			|| block->filters == NULL)
		return LZMA_PROG_ERROR;

	if (!lzma_check_is_supported(block->check))
		return LZMA_UNSUPPORTED_CHECK;

	// Size of a Block has to be a multiple of four, so limit the size
	// here already. This way we don't need to check it again when adding
	// Block Padding.
	out_size -= (out_size - *out_pos) & 3;

	// Get the size of the Check field.
	check_size = lzma_check_size(block->check);
	assert(check_size != UINT32_MAX);

	// Reserve space for the Check field.
	if (out_size - *out_pos <= check_size)
		return LZMA_BUF_ERROR;

	out_size -= check_size;

	// Do the actual compression.
	ret = block_encode_normal(block, allocator,
			in, in_size, out, out_pos, out_size);
	if (ret != LZMA_OK) {
		// If the error was something else than output buffer
		// becoming full, return the error now.
		if (ret != LZMA_BUF_ERROR)
			return ret;

		// The data was uncompressible (at least with the options
		// given to us) or the output buffer was too small. Use the
		// uncompressed chunks of LZMA2 to wrap the data into a valid
		// Block. If we haven't been given enough output space, even
		// this may fail.
		return_if_error(block_encode_uncompressed(block, in, in_size,
				out, out_pos, out_size));
	}

	assert(*out_pos <= out_size);

	// Block Padding. No buffer overflow here, because we already adjusted
	// out_size so that (out_size - out_start) is a multiple of four.
	// Thus, if the buffer is full, the loop body can never run.
	for (i = (size_t)(block->compressed_size); i & 3; ++i) {
		assert(*out_pos < out_size);
		out[(*out_pos)++] = 0x00;
	}

	// If there's no Check field, we are done now.
	if (check_size > 0) {
		// Calculate the integrity check. We reserved space for
		// the Check field earlier so we don't need to check for
		// available output space here.
		lzma_check_state check;
		lzma_check_init(&check, block->check);
		lzma_check_update(&check, block->check, in, in_size);
		lzma_check_finish(&check, block->check);

		memcpy(block->raw_check, check.buffer.u8, check_size);
		memcpy(out + *out_pos, check.buffer.u8, check_size);
		*out_pos += check_size;
	}

	return LZMA_OK;
}
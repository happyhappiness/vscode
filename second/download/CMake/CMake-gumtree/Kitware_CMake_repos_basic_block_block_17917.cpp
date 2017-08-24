{
	size_t in_pos = 0;
	uint8_t control = 0x01; // Dictionary reset
	lzma_filter *filters_orig;

	// TODO: Figure out if the last filter is LZMA2 or Subblock and use
	// that filter to encode the uncompressed chunks.

	// Use LZMA2 uncompressed chunks. We wouldn't need a dictionary at
	// all, but LZMA2 always requires a dictionary, so use the minimum
	// value to minimize memory usage of the decoder.
	lzma_options_lzma lzma2 = { LZMA_DICT_SIZE_MIN };

	lzma_filter filters[2];
	filters[0].id = LZMA_FILTER_LZMA2;
	filters[0].options = &lzma2;
	filters[1].id = LZMA_VLI_UNKNOWN;

	// Set the above filter options to *block temporarily so that we can
	// encode the Block Header.
	filters_orig = block->filters;
	block->filters = filters;

	if (lzma_block_header_size(block) != LZMA_OK) {
		block->filters = filters_orig;
		return LZMA_PROG_ERROR;
	}

	// Check that there's enough output space. The caller has already
	// set block->compressed_size to what lzma2_bound() has returned,
	// so we can reuse that value. We know that compressed_size is a
	// known valid VLI and header_size is a small value so their sum
	// will never overflow.
	assert(block->compressed_size == lzma2_bound(in_size));
	if (out_size - *out_pos
			< block->header_size + block->compressed_size) {
		block->filters = filters_orig;
		return LZMA_BUF_ERROR;
	}

	if (lzma_block_header_encode(block, out + *out_pos) != LZMA_OK) {
		block->filters = filters_orig;
		return LZMA_PROG_ERROR;
	}

	block->filters = filters_orig;
	*out_pos += block->header_size;

	// Encode the data using LZMA2 uncompressed chunks.

	while (in_pos < in_size) {
		size_t copy_size;

		// Control byte: Indicate uncompressed chunk, of which
		// the first resets the dictionary.
		out[(*out_pos)++] = control;
		control = 0x02; // No dictionary reset

		// Size of the uncompressed chunk
		copy_size = my_min(in_size - in_pos, LZMA2_CHUNK_MAX);
		out[(*out_pos)++] = (copy_size - 1) >> 8;
		out[(*out_pos)++] = (copy_size - 1) & 0xFF;

		// The actual data
		assert(*out_pos + copy_size <= out_size);
		memcpy(out + *out_pos, in + in_pos, copy_size);

		in_pos += copy_size;
		*out_pos += copy_size;
	}

	// End marker
	out[(*out_pos)++] = 0x00;
	assert(*out_pos <= out_size);

	return LZMA_OK;
}
{
	size_t out_size;
	size_t out_pos = 2;
	size_t filter_count = 0;

	// Validate everything but filters.
	if (lzma_block_unpadded_size(block) == 0
			|| !lzma_vli_is_valid(block->uncompressed_size))
		return LZMA_PROG_ERROR;

	// Indicate the size of the buffer _excluding_ the CRC32 field.
	out_size = block->header_size - 4;

	// Store the Block Header Size.
	out[0] = out_size / 4;

	// We write Block Flags in pieces.
	out[1] = 0x00;

	// Compressed Size
	if (block->compressed_size != LZMA_VLI_UNKNOWN) {
		return_if_error(lzma_vli_encode(block->compressed_size, NULL,
				out, &out_pos, out_size));

		out[1] |= 0x40;
	}

	// Uncompressed Size
	if (block->uncompressed_size != LZMA_VLI_UNKNOWN) {
		return_if_error(lzma_vli_encode(block->uncompressed_size, NULL,
				out, &out_pos, out_size));

		out[1] |= 0x80;
	}

	// Filter Flags
	if (block->filters == NULL || block->filters[0].id == LZMA_VLI_UNKNOWN)
		return LZMA_PROG_ERROR;

	do {
		// There can be a maximum of four filters.
		if (filter_count == LZMA_FILTERS_MAX)
			return LZMA_PROG_ERROR;

		return_if_error(lzma_filter_flags_encode(
				block->filters + filter_count,
				out, &out_pos, out_size));

	} while (block->filters[++filter_count].id != LZMA_VLI_UNKNOWN);

	out[1] |= filter_count - 1;

	// Padding
	memzero(out + out_pos, out_size - out_pos);

	// CRC32
	unaligned_write32le(out + out_size, lzma_crc32(out, out_size, 0));

	return LZMA_OK;
}
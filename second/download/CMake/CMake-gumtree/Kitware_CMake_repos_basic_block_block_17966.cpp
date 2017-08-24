{
	lzma_vli unpadded_size;

	// Validate the values that we are interested in i.e. all but
	// Uncompressed Size and the filters.
	//
	// NOTE: This function is used for validation too, so it is
	// essential that these checks are always done even if
	// Compressed Size is unknown.
	if (block == NULL || block->version != 0
			|| block->header_size < LZMA_BLOCK_HEADER_SIZE_MIN
			|| block->header_size > LZMA_BLOCK_HEADER_SIZE_MAX
			|| (block->header_size & 3)
			|| !lzma_vli_is_valid(block->compressed_size)
			|| block->compressed_size == 0
			|| (unsigned int)(block->check) > LZMA_CHECK_ID_MAX)
		return 0;

	// If Compressed Size is unknown, return that we cannot know
	// size of the Block either.
	if (block->compressed_size == LZMA_VLI_UNKNOWN)
		return LZMA_VLI_UNKNOWN;

	// Calculate Unpadded Size and validate it.
	unpadded_size = block->compressed_size
				+ block->header_size
				+ lzma_check_size(block->check);

	assert(unpadded_size >= UNPADDED_SIZE_MIN);
	if (unpadded_size > UNPADDED_SIZE_MAX)
		return 0;

	return unpadded_size;
}
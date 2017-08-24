{
	uint32_t container_size;
	lzma_vli compressed_size;

	// Validate everything but Uncompressed Size and filters.
	if (lzma_block_unpadded_size(block) == 0)
		return LZMA_PROG_ERROR;

	container_size = block->header_size
			+ lzma_check_size(block->check);

	// Validate that Compressed Size will be greater than zero.
	if (unpadded_size <= container_size)
		return LZMA_DATA_ERROR;

	// Calculate what Compressed Size is supposed to be.
	// If Compressed Size was present in Block Header,
	// compare that the new value matches it.
	compressed_size = unpadded_size - container_size;
	if (block->compressed_size != LZMA_VLI_UNKNOWN
			&& block->compressed_size != compressed_size)
		return LZMA_DATA_ERROR;

	block->compressed_size = compressed_size;

	return LZMA_OK;
}
{
	uint32_t crc;

	assert(2 * 4 + LZMA_STREAM_FLAGS_SIZE + sizeof(lzma_footer_magic)
			== LZMA_STREAM_HEADER_SIZE);

	if (options->version != 0)
		return LZMA_OPTIONS_ERROR;

	// Backward Size
	if (!is_backward_size_valid(options))
		return LZMA_PROG_ERROR;

	unaligned_write32le(out + 4, options->backward_size / 4 - 1);

	// Stream Flags
	if (stream_flags_encode(options, out + 2 * 4))
		return LZMA_PROG_ERROR;

	// CRC32
	crc = lzma_crc32(
			out + 4, 4 + LZMA_STREAM_FLAGS_SIZE, 0);

	unaligned_write32le(out, crc);

	// Magic
	memcpy(out + 2 * 4 + LZMA_STREAM_FLAGS_SIZE,
			lzma_footer_magic, sizeof(lzma_footer_magic));

	return LZMA_OK;
}
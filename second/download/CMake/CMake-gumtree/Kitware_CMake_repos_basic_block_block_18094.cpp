{
	uint32_t crc;

	assert(sizeof(lzma_header_magic) + LZMA_STREAM_FLAGS_SIZE
			+ 4 == LZMA_STREAM_HEADER_SIZE);

	if (options->version != 0)
		return LZMA_OPTIONS_ERROR;

	// Magic
	memcpy(out, lzma_header_magic, sizeof(lzma_header_magic));

	// Stream Flags
	if (stream_flags_encode(options, out + sizeof(lzma_header_magic)))
		return LZMA_PROG_ERROR;

	// CRC32 of the Stream Header
	crc = lzma_crc32(out + sizeof(lzma_header_magic),
			LZMA_STREAM_FLAGS_SIZE, 0);

	unaligned_write32le(out + sizeof(lzma_header_magic)
			+ LZMA_STREAM_FLAGS_SIZE, crc);

	return LZMA_OK;
}
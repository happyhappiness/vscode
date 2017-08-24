{
	uint32_t d;

	// Initialize the LZMA encoder.
	const lzma_filter_info filters[2] = {
	    { 0, &lzma_lzma_encoder_init, (void *)(options) },
	    { 0, NULL, NULL }
	};

	lzma_next_coder_init(&alone_encoder_init, next, allocator);

	if (next->coder == NULL) {
		next->coder = lzma_alloc(sizeof(lzma_coder), allocator);
		if (next->coder == NULL)
			return LZMA_MEM_ERROR;

		next->code = &alone_encode;
		next->end = &alone_encoder_end;
		next->coder->next = LZMA_NEXT_CODER_INIT;
	}

	// Basic initializations
	next->coder->sequence = SEQ_HEADER;
	next->coder->header_pos = 0;

	// Encode the header:
	// - Properties (1 byte)
	if (lzma_lzma_lclppb_encode(options, next->coder->header))
		return LZMA_OPTIONS_ERROR;

	// - Dictionary size (4 bytes)
	if (options->dict_size < LZMA_DICT_SIZE_MIN)
		return LZMA_OPTIONS_ERROR;

	// Round up to the next 2^n or 2^n + 2^(n - 1) depending on which
	// one is the next unless it is UINT32_MAX. While the header would
	// allow any 32-bit integer, we do this to keep the decoder of liblzma
	// accepting the resulting files.
	d = options->dict_size - 1;
	d |= d >> 2;
	d |= d >> 3;
	d |= d >> 4;
	d |= d >> 8;
	d |= d >> 16;
	if (d != UINT32_MAX)
		++d;

	unaligned_write32le(next->coder->header + 1, d);

	// - Uncompressed size (always unknown and using EOPM)
	memset(next->coder->header + 1 + 4, 0xFF, 8);

	return lzma_next_filter_init(&next->coder->next, allocator, filters);
}
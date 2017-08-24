{
	lzma_lz_options lz_options;

#ifdef HAVE_SMALL
	// We need that the CRC32 table has been initialized.
	lzma_crc32_init();
#endif

	// Allocate and initialize the base data structure.
	if (next->coder == NULL) {
		next->coder = lzma_alloc(sizeof(lzma_coder), allocator);
		if (next->coder == NULL)
			return LZMA_MEM_ERROR;

		next->code = &lz_encode;
		next->end = &lz_encoder_end;
		next->update = &lz_encoder_update;

		next->coder->lz.coder = NULL;
		next->coder->lz.code = NULL;
		next->coder->lz.end = NULL;

		next->coder->mf.buffer = NULL;
		next->coder->mf.hash = NULL;
		next->coder->mf.hash_size_sum = 0;
		next->coder->mf.sons_count = 0;

		next->coder->next = LZMA_NEXT_CODER_INIT;
	}

	// Initialize the LZ-based encoder.
	return_if_error(lz_init(&next->coder->lz, allocator,
			filters[0].options, &lz_options));

	// Setup the size information into next->coder->mf and deallocate
	// old buffers if they have wrong size.
	if (lz_encoder_prepare(&next->coder->mf, allocator, &lz_options))
		return LZMA_OPTIONS_ERROR;

	// Allocate new buffers if needed, and do the rest of
	// the initialization.
	if (lz_encoder_init(&next->coder->mf, allocator, &lz_options))
		return LZMA_MEM_ERROR;

	// Initialize the next filter in the chain, if any.
	return lzma_next_filter_init(&next->coder->next, allocator,
			filters + 1);
}
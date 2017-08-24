{
	// Old buffers must not exist when calling lz_encoder_prepare().
	lzma_mf mf = { NULL };

	// Setup the size information into mf.
	if (lz_encoder_prepare(&mf, NULL, lz_options))
		return UINT64_MAX;

	// Calculate the memory usage.
	return (uint64_t)(mf.hash_size_sum + mf.sons_count)
				* sizeof(uint32_t)
			+ (uint64_t)(mf.size) + sizeof(lzma_coder);
}
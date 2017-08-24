{
	lzma_lz_options lz_options;
	uint64_t lz_memusage;

	if (!is_options_valid(options))
		return UINT64_MAX;

	set_lz_options(&lz_options, options);

	lz_memusage = lzma_lz_encoder_memusage(&lz_options);
	if (lz_memusage == UINT64_MAX)
		return UINT64_MAX;

	return (uint64_t)(sizeof(lzma_coder)) + lz_memusage;
}
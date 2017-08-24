{
	lzma_filter_info filters[LZMA_FILTERS_MAX + 1];
	size_t count;
	size_t i;
	lzma_ret ret;

	// Do some basic validation and get the number of filters.
	return_if_error(validate_chain(options, &count));

	// Set the filter functions and copy the options pointer.
	if (is_encoder) {
		for (i = 0; i < count; ++i) {
			// The order of the filters is reversed in the
			// encoder. It allows more efficient handling
			// of the uncompressed data.
			const size_t j = count - i - 1;

			const lzma_filter_coder *const fc
					= coder_find(options[i].id);
			if (fc == NULL || fc->init == NULL)
				return LZMA_OPTIONS_ERROR;

			filters[j].id = options[i].id;
			filters[j].init = fc->init;
			filters[j].options = options[i].options;
		}
	} else {
		for (i = 0; i < count; ++i) {
			const lzma_filter_coder *const fc
					= coder_find(options[i].id);
			if (fc == NULL || fc->init == NULL)
				return LZMA_OPTIONS_ERROR;

			filters[i].id = options[i].id;
			filters[i].init = fc->init;
			filters[i].options = options[i].options;
		}
	}

	// Terminate the array.
	filters[count].id = LZMA_VLI_UNKNOWN;
	filters[count].init = NULL;

	// Initialize the filters.
	ret = lzma_next_filter_init(next, allocator, filters);
	if (ret != LZMA_OK)
		lzma_next_end(next, allocator);

	return ret;
}
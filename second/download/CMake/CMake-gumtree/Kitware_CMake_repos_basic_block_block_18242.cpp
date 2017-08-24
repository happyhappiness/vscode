{
	lzma_coder *coder;
	uint32_t log_size = 0;

	// Allocate lzma_coder if it wasn't already allocated.
	if (*coder_ptr == NULL) {
		*coder_ptr = lzma_alloc(sizeof(lzma_coder), allocator);
		if (*coder_ptr == NULL)
			return LZMA_MEM_ERROR;
	}

	coder = *coder_ptr;

	// Set compression mode. We haven't validates the options yet,
	// but it's OK here, since nothing bad happens with invalid
	// options in the code below, and they will get rejected by
	// lzma_lzma_encoder_reset() call at the end of this function.
	switch (options->mode) {
		case LZMA_MODE_FAST:
			coder->fast_mode = true;
			break;

		case LZMA_MODE_NORMAL: {
			coder->fast_mode = false;

			// Set dist_table_size.
			// Round the dictionary size up to next 2^n.
			while ((UINT32_C(1) << log_size) < options->dict_size)
				++log_size;

			coder->dist_table_size = log_size * 2;

			// Length encoders' price table size
			coder->match_len_encoder.table_size
				= options->nice_len + 1 - MATCH_LEN_MIN;
			coder->rep_len_encoder.table_size
				= options->nice_len + 1 - MATCH_LEN_MIN;
			break;
		}

		default:
			return LZMA_OPTIONS_ERROR;
	}

	// We don't need to write the first byte as literal if there is
	// a non-empty preset dictionary. encode_init() wouldn't even work
	// if there is a non-empty preset dictionary, because encode_init()
	// assumes that position is zero and previous byte is also zero.
	coder->is_initialized = options->preset_dict != NULL
			&& options->preset_dict_size > 0;
	coder->is_flushed = false;

	set_lz_options(lz_options, options);

	return lzma_lzma_encoder_reset(coder, options);
}
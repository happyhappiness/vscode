{
		uint32_t add;

		// Don't allow too many filters.
		if (i == LZMA_FILTERS_MAX)
			return LZMA_PROG_ERROR;

		return_if_error(lzma_filter_flags_size(&add,
				block->filters + i));

		size += add;
	}
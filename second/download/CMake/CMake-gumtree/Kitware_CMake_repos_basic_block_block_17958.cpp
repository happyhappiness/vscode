{
		// There can be a maximum of four filters.
		if (filter_count == LZMA_FILTERS_MAX)
			return LZMA_PROG_ERROR;

		return_if_error(lzma_filter_flags_encode(
				block->filters + filter_count,
				out, &out_pos, out_size));

	}
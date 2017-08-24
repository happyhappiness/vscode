{
	// Number of non-last filters that may change the size of the data
	// significantly (that is, more than 1-2 % or so).
	size_t changes_size_count = 0;

	// True if it is OK to add a new filter after the current filter.
	bool non_last_ok = true;

	// True if the last filter in the given chain is actually usable as
	// the last filter. Only filters that support embedding End of Payload
	// Marker can be used as the last filter in the chain.
	bool last_ok = false;

	size_t i = 0;

	// There must be at least one filter.
	if (filters == NULL || filters[0].id == LZMA_VLI_UNKNOWN)
		return LZMA_PROG_ERROR;

	do {
		size_t j;
		for (j = 0; filters[i].id != features[j].id; ++j)
			if (features[j].id == LZMA_VLI_UNKNOWN)
				return LZMA_OPTIONS_ERROR;

		// If the previous filter in the chain cannot be a non-last
		// filter, the chain is invalid.
		if (!non_last_ok)
			return LZMA_OPTIONS_ERROR;

		non_last_ok = features[j].non_last_ok;
		last_ok = features[j].last_ok;
		changes_size_count += features[j].changes_size;

	} while (filters[++i].id != LZMA_VLI_UNKNOWN);

	// There must be 1-4 filters. The last filter must be usable as
	// the last filter in the chain. A maximum of three filters are
	// allowed to change the size of the data.
	if (i > LZMA_FILTERS_MAX || !last_ok || changes_size_count > 3)
		return LZMA_OPTIONS_ERROR;

	*count = i;
	return LZMA_OK;
}
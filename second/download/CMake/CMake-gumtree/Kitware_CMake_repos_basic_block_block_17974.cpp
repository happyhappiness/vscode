{
	if (lzma_lzma_preset(&opt_easy->opt_lzma, preset))
		return true;

	opt_easy->filters[0].id = LZMA_FILTER_LZMA2;
	opt_easy->filters[0].options = &opt_easy->opt_lzma;
	opt_easy->filters[1].id = LZMA_VLI_UNKNOWN;

	return false;
}
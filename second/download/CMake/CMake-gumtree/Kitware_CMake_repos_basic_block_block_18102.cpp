{
	lzma_options_delta *opt;

	if (props_size != 1)
		return LZMA_OPTIONS_ERROR;

	opt = lzma_alloc(sizeof(lzma_options_delta), allocator);
	if (opt == NULL)
		return LZMA_MEM_ERROR;

	opt->type = LZMA_DELTA_TYPE_BYTE;
	opt->dist = props[0] + 1;

	*options = opt;

	return LZMA_OK;
}
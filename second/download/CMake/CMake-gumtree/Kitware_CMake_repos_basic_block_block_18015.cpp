{
	if (filter->id >= LZMA_FILTER_RESERVED_START)
		return LZMA_PROG_ERROR;

	return_if_error(lzma_properties_size(size, filter));

	*size += lzma_vli_size(filter->id) + lzma_vli_size(*size);

	return LZMA_OK;
}
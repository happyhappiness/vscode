{
	lzma_vli props_size;
	lzma_ret ret;
	
	// Set the pointer to NULL so the caller can always safely free it.
	filter->options = NULL;

	// Filter ID
	return_if_error(lzma_vli_decode(&filter->id, NULL,
			in, in_pos, in_size));

	if (filter->id >= LZMA_FILTER_RESERVED_START)
		return LZMA_DATA_ERROR;

	// Size of Properties
	return_if_error(lzma_vli_decode(&props_size, NULL,
			in, in_pos, in_size));

	// Filter Properties
	if (in_size - *in_pos < props_size)
		return LZMA_DATA_ERROR;

	ret = lzma_properties_decode(
			filter, allocator, in + *in_pos, props_size);

	*in_pos += props_size;

	return ret;
}
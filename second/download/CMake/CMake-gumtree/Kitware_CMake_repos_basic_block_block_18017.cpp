{
	uint32_t props_size;

	// Filter ID
	if (filter->id >= LZMA_FILTER_RESERVED_START)
		return LZMA_PROG_ERROR;

	return_if_error(lzma_vli_encode(filter->id, NULL,
			out, out_pos, out_size));

	// Size of Properties
	return_if_error(lzma_properties_size(&props_size, filter));
	return_if_error(lzma_vli_encode(props_size, NULL,
			out, out_pos, out_size));

	// Filter Properties
	if (out_size - *out_pos < props_size)
		return LZMA_PROG_ERROR;

	return_if_error(lzma_properties_encode(filter, out + *out_pos));

	*out_pos += props_size;

	return LZMA_OK;
}
{
	const lzma_filter_decoder *const fd = decoder_find(filter->id);

	// Make it always NULL so that the caller can always safely free() it.
	filter->options = NULL;

	if (fd == NULL)
		return LZMA_OPTIONS_ERROR;

	if (fd->props_decode == NULL)
		return props_size == 0 ? LZMA_OK : LZMA_OPTIONS_ERROR;

	return fd->props_decode(
			&filter->options, allocator, props, props_size);
}
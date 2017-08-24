{
	const lzma_options_lzma *const opt = options;

	if (lzma_lzma_lclppb_encode(opt, out))
		return LZMA_PROG_ERROR;

	unaligned_write32le(out + 1, opt->dict_size);

	return LZMA_OK;
}
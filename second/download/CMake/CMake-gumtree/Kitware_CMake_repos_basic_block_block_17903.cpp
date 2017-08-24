{
	lzma_next_coder_init(&auto_decoder_init, next, allocator);

	if (memlimit == 0)
		return LZMA_PROG_ERROR;

	if (flags & ~LZMA_SUPPORTED_FLAGS)
		return LZMA_OPTIONS_ERROR;

	if (next->coder == NULL) {
		next->coder = lzma_alloc(sizeof(lzma_coder), allocator);
		if (next->coder == NULL)
			return LZMA_MEM_ERROR;

		next->code = &auto_decode;
		next->end = &auto_decoder_end;
		next->get_check = &auto_decoder_get_check;
		next->memconfig = &auto_decoder_memconfig;
		next->coder->next = LZMA_NEXT_CODER_INIT;
	}

	next->coder->memlimit = memlimit;
	next->coder->flags = flags;
	next->coder->sequence = SEQ_INIT;

	return LZMA_OK;
}
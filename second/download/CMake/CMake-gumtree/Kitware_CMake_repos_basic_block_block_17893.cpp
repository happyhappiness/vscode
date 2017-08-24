{
	lzma_next_coder_init(&lzma_alone_decoder_init, next, allocator);

	if (memlimit == 0)
		return LZMA_PROG_ERROR;

	if (next->coder == NULL) {
		next->coder = lzma_alloc(sizeof(lzma_coder), allocator);
		if (next->coder == NULL)
			return LZMA_MEM_ERROR;

		next->code = &alone_decode;
		next->end = &alone_decoder_end;
		next->memconfig = &alone_decoder_memconfig;
		next->coder->next = LZMA_NEXT_CODER_INIT;
	}

	next->coder->sequence = SEQ_PROPERTIES;
	next->coder->picky = picky;
	next->coder->pos = 0;
	next->coder->options.dict_size = 0;
	next->coder->options.preset_dict = NULL;
	next->coder->options.preset_dict_size = 0;
	next->coder->uncompressed_size = 0;
	next->coder->memlimit = memlimit;
	next->coder->memusage = LZMA_MEMUSAGE_BASE;

	return LZMA_OK;
}
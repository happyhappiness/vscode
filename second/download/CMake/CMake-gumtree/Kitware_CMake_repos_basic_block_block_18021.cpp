{
		next->coder = lzma_alloc(sizeof(lzma_coder), allocator);
		if (next->coder == NULL)
			return LZMA_MEM_ERROR;

		next->code = &index_decode;
		next->end = &index_decoder_end;
		next->memconfig = &index_decoder_memconfig;
		next->coder->index = NULL;
	}
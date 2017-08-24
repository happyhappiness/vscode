{
		next->coder = lzma_alloc(sizeof(lzma_coder), allocator);
		if (next->coder == NULL)
			return LZMA_MEM_ERROR;

		next->code = &stream_decode;
		next->end = &stream_decoder_end;
		next->get_check = &stream_decoder_get_check;
		next->memconfig = &stream_decoder_memconfig;

		next->coder->block_decoder = LZMA_NEXT_CODER_INIT;
		next->coder->index_hash = NULL;
	}
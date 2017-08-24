{
		lz->coder = lzma_alloc(sizeof(lzma_coder), allocator);
		if (lz->coder == NULL)
			return LZMA_MEM_ERROR;

		lz->code = &lzma2_encode;
		lz->end = &lzma2_encoder_end;
		lz->options_update = &lzma2_encoder_options_update;

		lz->coder->lzma = NULL;
	}
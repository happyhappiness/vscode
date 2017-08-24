{
		next->coder = lzma_alloc(sizeof(lzma_coder), allocator);
		if (next->coder == NULL)
			return LZMA_MEM_ERROR;

		next->code = &lz_encode;
		next->end = &lz_encoder_end;
		next->update = &lz_encoder_update;

		next->coder->lz.coder = NULL;
		next->coder->lz.code = NULL;
		next->coder->lz.end = NULL;

		next->coder->mf.buffer = NULL;
		next->coder->mf.hash = NULL;
		next->coder->mf.hash_size_sum = 0;
		next->coder->mf.sons_count = 0;

		next->coder->next = LZMA_NEXT_CODER_INIT;
	}
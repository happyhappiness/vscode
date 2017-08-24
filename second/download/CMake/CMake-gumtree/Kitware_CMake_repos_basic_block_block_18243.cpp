{
		*coder_ptr = lzma_alloc(sizeof(lzma_coder), allocator);
		if (*coder_ptr == NULL)
			return LZMA_MEM_ERROR;
	}
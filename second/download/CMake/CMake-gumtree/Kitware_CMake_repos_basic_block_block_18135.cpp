(mf->hash == NULL) {
		mf->hash = lzma_alloc(alloc_count * sizeof(uint32_t),
				allocator);
		if (mf->hash == NULL)
			return true;
	}
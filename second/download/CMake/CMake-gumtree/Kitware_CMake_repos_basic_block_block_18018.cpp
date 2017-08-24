{
	*memusage = lzma_index_memusage(1, coder->count);
	*old_memlimit = coder->memlimit;

	if (new_memlimit != 0) {
		if (new_memlimit < *memusage)
			return LZMA_MEMLIMIT_ERROR;

		coder->memlimit = new_memlimit;
	}

	return LZMA_OK;
}
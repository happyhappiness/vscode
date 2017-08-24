{
	// Remember the pointer given by the application. We will set it
	// to point to the decoded Index only if decoding is successful.
	// Before that, keep it NULL so that applications can always safely
	// pass it to lzma_index_end() no matter did decoding succeed or not.
	coder->index_ptr = i;
	*i = NULL;

	// We always allocate a new lzma_index.
	coder->index = lzma_index_init(allocator);
	if (coder->index == NULL)
		return LZMA_MEM_ERROR;

	// Initialize the rest.
	coder->sequence = SEQ_INDICATOR;
	coder->memlimit = memlimit;
	coder->count = 0; // Needs to be initialized due to _memconfig().
	coder->pos = 0;
	coder->crc32 = 0;

	return LZMA_OK;
}
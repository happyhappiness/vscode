{
	// Initialize the Index hash used to verify the Index.
	coder->index_hash = lzma_index_hash_init(coder->index_hash, allocator);
	if (coder->index_hash == NULL)
		return LZMA_MEM_ERROR;

	// Reset the rest of the variables.
	coder->sequence = SEQ_STREAM_HEADER;
	coder->pos = 0;

	return LZMA_OK;
}
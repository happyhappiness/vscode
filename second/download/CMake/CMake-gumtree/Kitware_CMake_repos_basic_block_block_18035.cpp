{
	if (index_hash == NULL) {
		index_hash = lzma_alloc(sizeof(lzma_index_hash), allocator);
		if (index_hash == NULL)
			return NULL;
	}

	index_hash->sequence = SEQ_BLOCK;
	index_hash->blocks.blocks_size = 0;
	index_hash->blocks.uncompressed_size = 0;
	index_hash->blocks.count = 0;
	index_hash->blocks.index_list_size = 0;
	index_hash->records.blocks_size = 0;
	index_hash->records.uncompressed_size = 0;
	index_hash->records.count = 0;
	index_hash->records.index_list_size = 0;
	index_hash->unpadded_size = 0;
	index_hash->uncompressed_size = 0;
	index_hash->pos = 0;
	index_hash->crc32 = 0;

	// These cannot fail because LZMA_CHECK_BEST is known to be supported.
	(void)lzma_check_init(&index_hash->blocks.check, LZMA_CHECK_BEST);
	(void)lzma_check_init(&index_hash->records.check, LZMA_CHECK_BEST);

	return index_hash;
}
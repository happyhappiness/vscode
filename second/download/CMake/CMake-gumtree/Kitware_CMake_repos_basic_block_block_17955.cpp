{
		const uint32_t add = lzma_vli_size(block->compressed_size);
		if (add == 0 || block->compressed_size == 0)
			return LZMA_PROG_ERROR;

		size += add;
	}
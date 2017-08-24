(block->compressed_size != LZMA_VLI_UNKNOWN
			&& block->compressed_size != compressed_size)
		return LZMA_DATA_ERROR;
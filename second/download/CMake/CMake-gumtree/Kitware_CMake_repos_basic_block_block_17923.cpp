{
		// Compression was successful. Write the Block Header.
		block->compressed_size
				= *out_pos - (out_start + block->header_size);
		ret = lzma_block_header_encode(block, out + out_start);
		if (ret != LZMA_OK)
			ret = LZMA_PROG_ERROR;

	}
{
		return_if_error(lzma_vli_encode(block->uncompressed_size, NULL,
				out, &out_pos, out_size));

		out[1] |= 0x80;
	}
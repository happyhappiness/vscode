cksum = crc32(crc32(0, NULL, 0), state->out_block,
		    state->uncompressed_size)
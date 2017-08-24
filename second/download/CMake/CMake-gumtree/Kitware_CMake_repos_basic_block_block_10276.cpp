{
		/* Prepare a prefix 64k block for next block. */
		if (!state->flags.block_independence) {
			prefix64k = 64 * 1024;
			if (uncompressed_size < (ssize_t)prefix64k) {
				memcpy(state->out_block
					+ prefix64k - uncompressed_size,
				    read_buf + 4,
				    uncompressed_size);
				memset(state->out_block, 0,
				    prefix64k - uncompressed_size);
			} else {
				memcpy(state->out_block,
				    read_buf + 4
					+ uncompressed_size - prefix64k,
				    prefix64k);
			}
			state->decoded_size = 0;
		}
		state->unconsumed = 4 + uncompressed_size + checksum_size;
		*p = read_buf + 4;
		return uncompressed_size;
	}
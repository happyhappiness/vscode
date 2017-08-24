(uncompressed_size < (ssize_t)prefix64k) {
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
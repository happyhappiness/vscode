{
				memcpy(state->out_block,
				    read_buf + 4
					+ uncompressed_size - prefix64k,
				    prefix64k);
			}
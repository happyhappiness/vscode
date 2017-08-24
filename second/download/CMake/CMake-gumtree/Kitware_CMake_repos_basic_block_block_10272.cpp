(state->decoded_size < prefix64k) {
				memmove(state->out_block
					+ prefix64k - state->decoded_size,
				    state->out_block + prefix64k,
				    state->decoded_size);
				memset(state->out_block, 0,
				    prefix64k - state->decoded_size);
			} else {
				memmove(state->out_block,
				    state->out_block + state->decoded_size,
				    prefix64k);
			}
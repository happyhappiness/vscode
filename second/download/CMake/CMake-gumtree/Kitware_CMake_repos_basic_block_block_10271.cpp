{
				memmove(state->out_block,
				    state->out_block + state->decoded_size,
				    prefix64k);
			}
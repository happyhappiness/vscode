{
				state->eof = 1;
				*p = state->out_block;
				decompressed = state->stream.next_out
				    - state->out_block;
				return (decompressed);
			}
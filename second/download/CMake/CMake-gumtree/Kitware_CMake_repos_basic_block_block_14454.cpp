(state->bit_offset > 0) {
			while (state->bit_offset < state->code_len * 8) {
				ret = output_byte(f, state->bit_buf);
				if (ret != ARCHIVE_OK)
					return ret;
				state->bit_offset += 8;
				state->bit_buf = 0;
			}
		}
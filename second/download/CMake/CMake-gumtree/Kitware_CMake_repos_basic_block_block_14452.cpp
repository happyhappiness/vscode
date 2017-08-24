{
	       /*
		* Write the whole buffer, because the input side won't
		* discover the size increase until after it has read it.
		*/
		if (state->bit_offset > 0) {
			while (state->bit_offset < state->code_len * 8) {
				ret = output_byte(f, state->bit_buf);
				if (ret != ARCHIVE_OK)
					return ret;
				state->bit_offset += 8;
				state->bit_buf = 0;
			}
		}
		state->bit_buf = 0;
		state->bit_offset = 0;

		if (clear_flg) {
			state->code_len = 9;
			state->cur_maxcode = MAXCODE(state->code_len);
		} else {
			state->code_len++;
			if (state->code_len == 16)
				state->cur_maxcode = state->max_maxcode;
			else
				state->cur_maxcode = MAXCODE(state->code_len);
		}
	}
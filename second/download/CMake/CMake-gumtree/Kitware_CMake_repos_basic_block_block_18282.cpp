{ // speed optimization
		// try literal + rep0
		const uint8_t *const buf_back = buf - reps[0] - 1;
		const uint32_t limit = my_min(buf_avail_full, nice_len + 1);

		uint32_t len_test = 1;
		while (len_test < limit && buf[len_test] == buf_back[len_test])
			++len_test;

		--len_test;

		if (len_test >= 2) {
			uint32_t pos_state_next;
			uint32_t next_rep_match_price;
			uint32_t offset;
			uint32_t cur_and_len_price;

			lzma_lzma_state state_2 = state;
			update_literal(state_2);

			pos_state_next = (position + 1) & coder->pos_mask;
			next_rep_match_price = cur_and_1_price
					+ rc_bit_1_price(coder->is_match[state_2][pos_state_next])
					+ rc_bit_1_price(coder->is_rep[state_2]);

			//for (; len_test >= 2; --len_test) {
			offset = cur + 1 + len_test;

			while (len_end < offset)
				coder->opts[++len_end].price = RC_INFINITY_PRICE;

			cur_and_len_price = next_rep_match_price
					+ get_rep_price(coder, 0, len_test,
						state_2, pos_state_next);

			if (cur_and_len_price < coder->opts[offset].price) {
				coder->opts[offset].price = cur_and_len_price;
				coder->opts[offset].pos_prev = cur + 1;
				coder->opts[offset].back_prev = 0;
				coder->opts[offset].prev_1_is_literal = true;
				coder->opts[offset].prev_2 = false;
			}
			//}
		}
	}
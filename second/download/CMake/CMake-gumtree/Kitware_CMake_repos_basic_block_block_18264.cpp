{
		uint32_t len_test;
		uint32_t i = 0;

		const uint32_t normal_match_price = match_price
				+ rc_bit_0_price(coder->is_rep[state]);

		while (len_end < cur + new_len)
			coder->opts[++len_end].price = RC_INFINITY_PRICE;

		while (start_len > coder->matches[i].len)
			++i;

		for (len_test = start_len; ; ++len_test) {
			const uint32_t cur_back = coder->matches[i].dist;
			uint32_t cur_and_len_price = normal_match_price
					+ get_pos_len_price(coder,
						cur_back, len_test, pos_state);

			if (cur_and_len_price < coder->opts[cur + len_test].price) {
				coder->opts[cur + len_test].price = cur_and_len_price;
				coder->opts[cur + len_test].pos_prev = cur;
				coder->opts[cur + len_test].back_prev
						= cur_back + REP_DISTANCES;
				coder->opts[cur + len_test].prev_1_is_literal = false;
			}

			if (len_test == coder->matches[i].len) {
				// Try Match + Literal + Rep0
				const uint8_t *const buf_back = buf - cur_back - 1;
				uint32_t len_test_2 = len_test + 1;
				const uint32_t limit = my_min(buf_avail_full,
						len_test_2 + nice_len);

				for (; len_test_2 < limit &&
						buf[len_test_2] == buf_back[len_test_2];
						++len_test_2) ;

				len_test_2 -= len_test + 1;

				if (len_test_2 >= 2) {
					uint32_t pos_state_next;
					uint32_t cur_and_len_literal_price;
					uint32_t next_rep_match_price;
					uint32_t offset;

					lzma_lzma_state state_2 = state;
					update_match(state_2);
					pos_state_next = (position + len_test) & coder->pos_mask;

					cur_and_len_literal_price = cur_and_len_price
							+ rc_bit_0_price(
								coder->is_match[state_2][pos_state_next])
							+ get_literal_price(coder,
								position + len_test,
								buf[len_test - 1],
								true,
								buf_back[len_test],
								buf[len_test]);

					update_literal(state_2);
					pos_state_next = (pos_state_next + 1) & coder->pos_mask;

					next_rep_match_price
							= cur_and_len_literal_price
							+ rc_bit_1_price(
								coder->is_match[state_2][pos_state_next])
							+ rc_bit_1_price(coder->is_rep[state_2]);

					// for(; len_test_2 >= 2; --len_test_2) {
					offset = cur + len_test + 1 + len_test_2;

					while (len_end < offset)
						coder->opts[++len_end].price = RC_INFINITY_PRICE;

					cur_and_len_price = next_rep_match_price
							+ get_rep_price(coder, 0, len_test_2,
								state_2, pos_state_next);

					if (cur_and_len_price < coder->opts[offset].price) {
						coder->opts[offset].price = cur_and_len_price;
						coder->opts[offset].pos_prev = cur + len_test + 1;
						coder->opts[offset].back_prev = 0;
						coder->opts[offset].prev_1_is_literal = true;
						coder->opts[offset].prev_2 = true;
						coder->opts[offset].pos_prev_2 = cur;
						coder->opts[offset].back_prev_2
								= cur_back + REP_DISTANCES;
					}
					//}
				}

				if (++i == matches_count)
					break;
			}
		}
	}
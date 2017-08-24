{
			uint32_t pos_state_next;
			uint32_t cur_and_len_literal_price;
			uint32_t next_rep_match_price;
			uint32_t offset;
			uint32_t cur_and_len_price;

			lzma_lzma_state state_2 = state;
			update_long_rep(state_2);

			pos_state_next = (position + len_test) & coder->pos_mask;

			cur_and_len_literal_price = price
					+ get_len_price(&coder->rep_len_encoder,
						len_test, pos_state)
					+ rc_bit_0_price(coder->is_match[state_2][pos_state_next])
					+ get_literal_price(coder, position + len_test,
						buf[len_test - 1], true,
						buf_back[len_test], buf[len_test]);

			update_literal(state_2);

			pos_state_next = (position + len_test + 1) & coder->pos_mask;

			next_rep_match_price = cur_and_len_literal_price
					+ rc_bit_1_price(coder->is_match[state_2][pos_state_next])
					+ rc_bit_1_price(coder->is_rep[state_2]);

			//for(; len_test_2 >= 2; len_test_2--) {
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
				coder->opts[offset].back_prev_2 = rep_index;
			}
			//}
		}
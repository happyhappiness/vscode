(rep_index = 0; rep_index < REP_DISTANCES; ++rep_index) {
		uint32_t len_test, len_test_2, len_test_temp;
		uint32_t price, limit;

		const uint8_t *const buf_back = buf - reps[rep_index] - 1;
		if (not_equal_16(buf, buf_back))
			continue;

		for (len_test = 2; len_test < buf_avail
				&& buf[len_test] == buf_back[len_test];
				++len_test) ;

		while (len_end < cur + len_test)
			coder->opts[++len_end].price = RC_INFINITY_PRICE;

		len_test_temp = len_test;
		price = rep_match_price + get_pure_rep_price(
				coder, rep_index, state, pos_state);

		do {
			const uint32_t cur_and_len_price = price
					+ get_len_price(&coder->rep_len_encoder,
							len_test, pos_state);

			if (cur_and_len_price < coder->opts[cur + len_test].price) {
				coder->opts[cur + len_test].price = cur_and_len_price;
				coder->opts[cur + len_test].pos_prev = cur;
				coder->opts[cur + len_test].back_prev = rep_index;
				coder->opts[cur + len_test].prev_1_is_literal = false;
			}
		} while (--len_test >= 2);

		len_test = len_test_temp;

		if (rep_index == 0)
			start_len = len_test + 1;


		len_test_2 = len_test + 1;
		limit = my_min(buf_avail_full,
				len_test_2 + nice_len);
		for (; len_test_2 < limit
				&& buf[len_test_2] == buf_back[len_test_2];
				++len_test_2) ;

		len_test_2 -= len_test + 1;

		if (len_test_2 >= 2) {
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
	}